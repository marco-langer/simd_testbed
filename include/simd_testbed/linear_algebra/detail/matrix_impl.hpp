#ifndef SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_IMPL_HPP
#define SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_IMPL_HPP

#include <immintrin.h>

#include <array>
#include <concepts>
#include <cstdint>

namespace st {

template <typename T, std::size_t Rows, std::size_t Cols>
class basic_matrix;

namespace detail {

// TODO check alternatives to mask load/store for handling residual columns

// LUTs for mask load/store
constexpr std::uint32_t ZR32 = 0;
constexpr std::uint32_t MV32 = 0x8000'0000;
alignas (32) constexpr auto mask_lut32 = std::array<std::array<std::uint32_t, 8>, 8>
{{
    {ZR32, ZR32, ZR32, ZR32, ZR32, ZR32, ZR32, ZR32},
    {MV32, ZR32, ZR32, ZR32, ZR32, ZR32, ZR32, ZR32},
    {MV32, MV32, ZR32, ZR32, ZR32, ZR32, ZR32, ZR32},
    {MV32, MV32, MV32, ZR32, ZR32, ZR32, ZR32, ZR32},
    {MV32, MV32, MV32, MV32, ZR32, ZR32, ZR32, ZR32},
    {MV32, MV32, MV32, MV32, MV32, ZR32, ZR32, ZR32},
    {MV32, MV32, MV32, MV32, MV32, MV32, ZR32, ZR32},
    {MV32, MV32, MV32, MV32, MV32, MV32, MV32, ZR32}
}};
constexpr std::uint64_t ZR64 = 0;
constexpr std::uint64_t MV64 = 0x8000'0000'0000'0000;
alignas (32) constexpr auto mask_lut64 = std::array<std::array<std::uint64_t, 4>, 4>
{{
    {ZR64, ZR64, ZR64, ZR64},
    {MV64, ZR64, ZR64, ZR64},
    {MV64, MV64, ZR64, ZR64},
    {MV64, MV64, MV64, ZR64}
}};

template
<
    typename T,
    std::size_t RowsLhs, std::size_t ColsLhs,
    std::size_t RowsRhs, std::size_t ColsRhs
>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, RowsLhs, ColsLhs> const& lhs,
        basic_matrix<T, RowsRhs, ColsRhs> const& rhs) noexcept
    -> basic_matrix<T, RowsLhs, ColsRhs>
    requires (ColsLhs == RowsRhs && std::same_as<T, float>)
{
    basic_matrix<T, RowsLhs, ColsRhs> result;

    T const* lhs_data = &*lhs.begin();
    T const* rhs_data = &*rhs.begin();
    T* result_data = &*result.begin();

    constexpr std::size_t simd_elements = 8;
    constexpr std::size_t residual_cols = result.cols % simd_elements;
    __m256i residual_mask = _mm256_load_si256(reinterpret_cast<__m256i const*>(mask_lut32[residual_cols].data()));

    for (std::size_t i = 0; i < result.rows; ++i)
    {
        std::size_t j = 0;
        for (; j + simd_elements < result.rows; j += simd_elements)
        {
            __m256 result_vals = _mm256_setzero_ps();
            for (std::size_t k = 0; k < lhs.cols; ++k)
            {
                __m256 lhs_vals = _mm256_broadcast_ss(&lhs_data[i * lhs.cols + k]);
                __m256 rhs_vals = _mm256_loadu_ps(&rhs_data[k * rhs.cols + j]);
                result_vals = _mm256_fmadd_ps(lhs_vals, rhs_vals, result_vals);
            }
            _mm256_storeu_ps(&result_data[i * result.cols + j], result_vals);
        }

        if constexpr (residual_cols > 0)
        {
            __m256 result_vals = _mm256_setzero_ps();
            for (std::size_t k = 0; k < lhs.cols; ++k)
            {
                __m256 lhs_vals = _mm256_broadcast_ss(&lhs_data[i * lhs.cols + k]);
                __m256 rhs_vals = _mm256_maskload_ps(&rhs_data[k * rhs.cols + j], residual_mask);
                result_vals = _mm256_fmadd_ps(lhs_vals, rhs_vals, result_vals);
            }
            _mm256_maskstore_ps(&result_data[i * result.cols + j], residual_mask, result_vals);
        }
    }
    return result;
}

template
<
    typename T,
    std::size_t RowsLhs, std::size_t ColsLhs,
    std::size_t RowsRhs, std::size_t ColsRhs
>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, RowsLhs, ColsLhs> const& lhs,
        basic_matrix<T, RowsRhs, ColsRhs> const& rhs) noexcept
    -> basic_matrix<T, RowsLhs, ColsRhs>
    requires (ColsLhs == RowsRhs && std::same_as<T, double>)
{
    basic_matrix<T, RowsLhs, ColsRhs> result;

    T const* lhs_data = &*lhs.begin();
    T const* rhs_data = &*rhs.begin();
    T* result_data = &*result.begin();

    constexpr std::size_t simd_elements = 4;
    constexpr std::size_t residual_cols = result.cols % simd_elements;
    __m256i residual_mask = _mm256_load_si256(reinterpret_cast<__m256i const*>(mask_lut64[residual_cols].data()));

    for (std::size_t i = 0; i < result.rows; ++i)
    {
        std::size_t j = 0;
        for (; j + simd_elements < result.rows; j += simd_elements)
        {
            __m256d result_vals = _mm256_setzero_pd();
            for (std::size_t k = 0; k < lhs.cols; ++k)
            {
                __m256d lhs_vals = _mm256_broadcast_sd(&lhs_data[i * lhs.cols + k]);
                __m256d rhs_vals = _mm256_loadu_pd(&rhs_data[k * rhs.cols + j]);
                result_vals = _mm256_fmadd_pd(lhs_vals, rhs_vals, result_vals);
            }
            _mm256_storeu_pd(&result_data[i * result.cols + j], result_vals);
        }

        if constexpr (residual_cols > 0)
        {
            __m256d result_vals = _mm256_setzero_pd();
            for (std::size_t k = 0; k < lhs.cols; ++k)
            {
                __m256d lhs_vals = _mm256_broadcast_sd(&lhs_data[i * lhs.cols + k]);
                __m256d rhs_vals = _mm256_maskload_pd(&rhs_data[k * rhs.cols + j], residual_mask);
                result_vals = _mm256_fmadd_pd(lhs_vals, rhs_vals, result_vals);
            }
            _mm256_maskstore_pd(&result_data[i * result.cols + j], residual_mask, result_vals);
        }
    }
    return result;
}

template <typename T>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, 4, 4> const& lhs,
        basic_matrix<T, 4, 4> const& rhs) noexcept
    -> basic_matrix<T, 4, 4>
    requires std::same_as<T, float>
{
    basic_matrix<T, 4, 4> result;
    T const* lhs_data = &*lhs.begin();
    T const* rhs_data = &*rhs.begin();
    T* result_data = &*result.begin();

    __m128 rhs_row0 = _mm_load_ps(&rhs_data[0]);
    __m128 rhs_row1 = _mm_load_ps(&rhs_data[4]);
    __m128 rhs_row2 = _mm_load_ps(&rhs_data[8]);
    __m128 rhs_row3 = _mm_load_ps(&rhs_data[12]);

    // result row0
    __m128 lhs_00 = _mm_broadcast_ss(&lhs_data[0]);
    __m128 lhs_01 = _mm_broadcast_ss(&lhs_data[1]);
    __m128 lhs_02 = _mm_broadcast_ss(&lhs_data[2]);
    __m128 lhs_03 = _mm_broadcast_ss(&lhs_data[3]);

    __m128 result_row0 = _mm_mul_ps(lhs_00, rhs_row0);
    result_row0 = _mm_fmadd_ps(lhs_01, rhs_row1, result_row0);
    result_row0 = _mm_fmadd_ps(lhs_02, rhs_row2, result_row0);
    result_row0 = _mm_fmadd_ps(lhs_03, rhs_row3, result_row0);
    _mm_store_ps(&result_data[0], result_row0);

    // result row1
    __m128 lhs_10 = _mm_broadcast_ss(&lhs_data[4]);
    __m128 lhs_11 = _mm_broadcast_ss(&lhs_data[5]);
    __m128 lhs_12 = _mm_broadcast_ss(&lhs_data[6]);
    __m128 lhs_13 = _mm_broadcast_ss(&lhs_data[7]);

    __m128 result_row1 = _mm_mul_ps(lhs_10, rhs_row0);
    result_row1 = _mm_fmadd_ps(lhs_11, rhs_row1, result_row1);
    result_row1 = _mm_fmadd_ps(lhs_12, rhs_row2, result_row1);
    result_row1 = _mm_fmadd_ps(lhs_13, rhs_row3, result_row1);
    _mm_store_ps(&result_data[4], result_row1);

    // result row2
    __m128 lhs_20 = _mm_broadcast_ss(&lhs_data[8]);
    __m128 lhs_21 = _mm_broadcast_ss(&lhs_data[9]);
    __m128 lhs_22 = _mm_broadcast_ss(&lhs_data[10]);
    __m128 lhs_23 = _mm_broadcast_ss(&lhs_data[11]);

    __m128 result_row2 = _mm_mul_ps(lhs_20, rhs_row0);
    result_row2 = _mm_fmadd_ps(lhs_21, rhs_row1, result_row2);
    result_row2 = _mm_fmadd_ps(lhs_22, rhs_row2, result_row2);
    result_row2 = _mm_fmadd_ps(lhs_23, rhs_row3, result_row2);
    _mm_store_ps(&result_data[8], result_row2);

    // result row3
    __m128 lhs_30 = _mm_broadcast_ss(&lhs_data[12]);
    __m128 lhs_31 = _mm_broadcast_ss(&lhs_data[13]);
    __m128 lhs_32 = _mm_broadcast_ss(&lhs_data[14]);
    __m128 lhs_33 = _mm_broadcast_ss(&lhs_data[15]);

    __m128 result_row3 = _mm_mul_ps(lhs_30, rhs_row0);
    result_row3 = _mm_fmadd_ps(lhs_31, rhs_row1, result_row3);
    result_row3 = _mm_fmadd_ps(lhs_32, rhs_row2, result_row3);
    result_row3 = _mm_fmadd_ps(lhs_33, rhs_row3, result_row3);
    _mm_store_ps(&result_data[12], result_row3);

    return result;
}

template <typename T>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, 4, 4> const& lhs,
        basic_matrix<T, 4, 4> const& rhs) noexcept
    -> basic_matrix<T, 4, 4>
    requires std::same_as<T, double>
{
    basic_matrix<T, 4, 4> result;
    T const* lhs_data = &*lhs.begin();
    T const* rhs_data = &*rhs.begin();
    T* result_data = &*result.begin();

    __m256d rhs_row0 = _mm256_load_pd(&rhs_data[0]);
    __m256d rhs_row1 = _mm256_load_pd(&rhs_data[4]);
    __m256d rhs_row2 = _mm256_load_pd(&rhs_data[8]);
    __m256d rhs_row3 = _mm256_load_pd(&rhs_data[12]);

    // result row0
    __m256d lhs_00 = _mm256_broadcast_sd(&lhs_data[0]);
    __m256d lhs_01 = _mm256_broadcast_sd(&lhs_data[1]);
    __m256d lhs_02 = _mm256_broadcast_sd(&lhs_data[2]);
    __m256d lhs_03 = _mm256_broadcast_sd(&lhs_data[3]);

    __m256d result_row0 = _mm256_mul_pd(lhs_00, rhs_row0);
    result_row0 = _mm256_fmadd_pd(lhs_01, rhs_row1, result_row0);
    result_row0 = _mm256_fmadd_pd(lhs_02, rhs_row2, result_row0);
    result_row0 = _mm256_fmadd_pd(lhs_03, rhs_row3, result_row0);
    _mm256_store_pd(&result_data[0], result_row0);

    // result row1
    __m256d lhs_10 = _mm256_broadcast_sd(&lhs_data[4]);
    __m256d lhs_11 = _mm256_broadcast_sd(&lhs_data[5]);
    __m256d lhs_12 = _mm256_broadcast_sd(&lhs_data[6]);
    __m256d lhs_13 = _mm256_broadcast_sd(&lhs_data[7]);

    __m256d result_row1 = _mm256_mul_pd(lhs_10, rhs_row0);
    result_row1 = _mm256_fmadd_pd(lhs_11, rhs_row1, result_row1);
    result_row1 = _mm256_fmadd_pd(lhs_12, rhs_row2, result_row1);
    result_row1 = _mm256_fmadd_pd(lhs_13, rhs_row3, result_row1);
    _mm256_store_pd(&result_data[4], result_row1);

    // result row2
    __m256d lhs_20 = _mm256_broadcast_sd(&lhs_data[8]);
    __m256d lhs_21 = _mm256_broadcast_sd(&lhs_data[9]);
    __m256d lhs_22 = _mm256_broadcast_sd(&lhs_data[10]);
    __m256d lhs_23 = _mm256_broadcast_sd(&lhs_data[11]);

    __m256d result_row2 = _mm256_mul_pd(lhs_20, rhs_row0);
    result_row2 = _mm256_fmadd_pd(lhs_21, rhs_row1, result_row2);
    result_row2 = _mm256_fmadd_pd(lhs_22, rhs_row2, result_row2);
    result_row2 = _mm256_fmadd_pd(lhs_23, rhs_row3, result_row2);
    _mm256_store_pd(&result_data[8], result_row2);

    // result row3
    __m256d lhs_30 = _mm256_broadcast_sd(&lhs_data[12]);
    __m256d lhs_31 = _mm256_broadcast_sd(&lhs_data[13]);
    __m256d lhs_32 = _mm256_broadcast_sd(&lhs_data[14]);
    __m256d lhs_33 = _mm256_broadcast_sd(&lhs_data[15]);

    __m256d result_row3 = _mm256_mul_pd(lhs_30, rhs_row0);
    result_row3 = _mm256_fmadd_pd(lhs_31, rhs_row1, result_row3);
    result_row3 = _mm256_fmadd_pd(lhs_32, rhs_row2, result_row3);
    result_row3 = _mm256_fmadd_pd(lhs_33, rhs_row3, result_row3);
    _mm256_store_pd(&result_data[12], result_row3);

    return result;
}

template <typename T>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, 4, 4> const& lhs,
        basic_matrix<T, 4, 1> const& rhs) noexcept
    -> basic_matrix<T, 4, 1>
    requires std::same_as<T, float>
{
    basic_matrix<T, 4, 1> result;
    T const* mat_data = &*lhs.begin();
    T const* vec_data = &*rhs.begin();
    T* result_data = &*result.begin();

    // load matrix rows and transpose to them get columns
    __m128 mat_row_0 = _mm_loadu_ps(&mat_data[0]);
    __m128 mat_row_1 = _mm_loadu_ps(&mat_data[4]);
    __m128 mat_row_2 = _mm_loadu_ps(&mat_data[8]);
    __m128 mat_row_3 = _mm_loadu_ps(&mat_data[12]);
    __m128 tmp_0 = _mm_unpacklo_ps(mat_row_0, mat_row_1);
    __m128 tmp_1 = _mm_unpackhi_ps(mat_row_0, mat_row_1);
    __m128 tmp_2 = _mm_unpacklo_ps(mat_row_2, mat_row_3);
    __m128 tmp_3 = _mm_unpackhi_ps(mat_row_2, mat_row_3);
    __m128 mat_col_0 = _mm_movelh_ps(tmp_0, tmp_2);
    __m128 mat_col_1 = _mm_movehl_ps(tmp_2, tmp_0);
    __m128 mat_col_2 = _mm_movelh_ps(tmp_1, tmp_3);
    __m128 mat_col_3 = _mm_movehl_ps(tmp_3, tmp_1);

    // load vector
    __m128 vec_0 = _mm_broadcast_ss(&vec_data[0]);
    __m128 vec_1 = _mm_broadcast_ss(&vec_data[1]);
    __m128 vec_2 = _mm_broadcast_ss(&vec_data[2]);
    __m128 vec_3 = _mm_broadcast_ss(&vec_data[3]);

    // multiply matrix and vector
    __m128 result_vec = _mm_mul_ps(mat_col_0, vec_0);
    result_vec = _mm_fmadd_ps(mat_col_1, vec_1, result_vec);
    result_vec = _mm_fmadd_ps(mat_col_2, vec_2, result_vec);
    result_vec = _mm_fmadd_ps(mat_col_3, vec_3, result_vec);
    _mm_storeu_ps(&result_data[0], result_vec);

    return result;
}

template <typename T>
inline constexpr auto
matrix_mul_intrin(
        basic_matrix<T, 4, 4> const& lhs,
        basic_matrix<T, 4, 1> const& rhs) noexcept
    -> basic_matrix<T, 4, 1>
    requires std::same_as<T, double>
{
    basic_matrix<T, 4, 1> result;
    T const* mat_data = &*lhs.begin();
    T const* vec_data = &*rhs.begin();
    T* result_data = &*result.begin();

    // load matrix rows and transpose to them get columns
    __m256d mat_row_0 = _mm256_loadu_pd(&mat_data[0]);
    __m256d mat_row_1 = _mm256_loadu_pd(&mat_data[4]);
    __m256d mat_row_2 = _mm256_loadu_pd(&mat_data[8]);
    __m256d mat_row_3 = _mm256_loadu_pd(&mat_data[12]);
    __m256d tmp_0 = _mm256_unpacklo_pd(mat_row_0, mat_row_1);
    __m256d tmp_1 = _mm256_unpackhi_pd(mat_row_0, mat_row_1);
    __m256d tmp_2 = _mm256_unpacklo_pd(mat_row_2, mat_row_3);
    __m256d tmp_3 = _mm256_unpackhi_pd(mat_row_2, mat_row_3);
    __m256d mat_col_0 = _mm256_permute2f128_pd(tmp_0, tmp_2, 0x20);
    __m256d mat_col_1 = _mm256_permute2f128_pd(tmp_1, tmp_3, 0x20);
    __m256d mat_col_2 = _mm256_permute2f128_pd(tmp_0, tmp_2, 0x31);
    __m256d mat_col_3 = _mm256_permute2f128_pd(tmp_1, tmp_3, 0x31);

    // load vector
    __m256d vec_0 = _mm256_broadcast_sd(&vec_data[0]);
    __m256d vec_1 = _mm256_broadcast_sd(&vec_data[1]);
    __m256d vec_2 = _mm256_broadcast_sd(&vec_data[2]);
    __m256d vec_3 = _mm256_broadcast_sd(&vec_data[3]);

    // multiply matrix and vector
    __m256d result_vec = _mm256_mul_pd(mat_col_0, vec_0);
    result_vec = _mm256_fmadd_pd(mat_col_1, vec_1, result_vec);
    result_vec = _mm256_fmadd_pd(mat_col_2, vec_2, result_vec);
    result_vec = _mm256_fmadd_pd(mat_col_3, vec_3, result_vec);
    _mm256_storeu_pd(&result_data[0], result_vec);

    return result;
}

} // namespace detail
} // namespace st

#endif
