#ifndef SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_IMPL_HPP
#define SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_IMPL_HPP

#include <cstdint>

namespace st {

template <typename T, std::size_t Rows, std::size_t Cols>
class basic_matrix;

namespace detail {

template
<
    typename T,
    std::size_t RowsLhs, std::size_t ColsLhs,
    std::size_t RowsRhs, std::size_t ColsRhs
>
[[nodiscard]] constexpr auto
matrix_mul(
        basic_matrix<T, RowsLhs, ColsLhs> const& lhs,
        basic_matrix<T, RowsRhs, ColsRhs> const& rhs) noexcept
    -> basic_matrix<T, RowsLhs, ColsRhs>
    requires (ColsLhs == RowsRhs)
{
    auto result_matrix = basic_matrix<T, RowsLhs, ColsRhs>{};
    for (std::size_t i = 0; i < lhs.rows; ++i)
    {
        for (std::size_t j = 0; j < rhs.cols; ++j)
        {
            for (std::size_t ii = 0; ii < lhs.cols; ++ii)
            {
                result_matrix(i, j) += lhs(i, ii) * rhs(ii, j);
            }
        }
    }
    return result_matrix;
}

} // namespace detail
} // namespace st

#endif
