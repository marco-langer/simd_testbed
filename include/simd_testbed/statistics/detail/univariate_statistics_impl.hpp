#ifndef SIMD_TESTBED_STATISTICS_DETAIL_MEAN_IMPL_HPP
#define SIMD_TESTBED_STATISTICS_DETAIL_MEAN_IMPL_HPP

#include <immintrin.h>
#include <cstdint>

namespace st::detail {

auto hsum_ps_sse3(__m128 v) -> float {
    __m128 shuf = _mm_movehdup_ps(v);        // broadcast elements 3,1 to 2,0
    __m128 sums = _mm_add_ps(v, shuf);
    shuf        = _mm_movehl_ps(shuf, sums); // high half -> low half
    sums        = _mm_add_ss(sums, shuf);
    return        _mm_cvtss_f32(sums);
}

auto hsum_ps_avx(__m256 v) -> float
{
    __m128 vlow  = _mm256_extractf128_ps(v, 0);
    __m128 vhigh = _mm256_extractf128_ps(v, 1);
    return hsum_ps_sse3(_mm_add_ps(vlow, vhigh));
}

auto hsum_pd_avx(__m256d v) -> double
{
    __m128d vlow  = _mm256_extractf128_pd(v, 0);
    __m128d vhigh = _mm256_extractf128_pd(v, 1);
    __m128d vsum  = _mm_add_pd(vlow, vhigh);
    vsum          = _mm_hadd_pd(vsum, vsum);
    return          _mm_cvtsd_f64(vsum);
}

template <typename InIt>
auto mean_impl(InIt first, std::ptrdiff_t n)
    -> typename std::iterator_traits<InIt>::value_type
    requires std::same_as<typename std::iterator_traits<InIt>::value_type, float>
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr std::ptrdiff_t simd_elements = 256 / sizeof(T) / 8;
    T const* data = &*first;

    __m256 sum_8xf32 = _mm256_setzero_ps();
    std::ptrdiff_t i = 0;
    for (; n - simd_elements >= i; i += simd_elements)
    {
        __m256 values_8x32f = _mm256_loadu_ps(&data[i]);
        sum_8xf32 = _mm256_add_ps(values_8x32f, sum_8xf32);
    }
    T sum = hsum_ps_avx(sum_8xf32);

    // TODO unroll to prevent compiler optimizations
    for(; i < n; ++i)
    {
        sum += data[i];
    }

    return sum / T(n);
}

template <typename InIt>
auto mean_impl(InIt first, std::ptrdiff_t n)
    -> typename std::iterator_traits<InIt>::value_type
    requires std::same_as<typename std::iterator_traits<InIt>::value_type, double>
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr std::ptrdiff_t simd_elements = 256 / sizeof(T) / 8;
    T const* data = &*first;

    __m256d sum_4xf64 = _mm256_setzero_pd();
    std::ptrdiff_t i = 0;
    for (; n - simd_elements >= i; i += simd_elements)
    {
        __m256d values_4x64f = _mm256_loadu_pd(&data[i]);
        sum_4xf64 = _mm256_add_pd(values_4x64f, sum_4xf64);
    }
    T sum = hsum_pd_avx(sum_4xf64);

    // TODO unroll to prevent compiler optimizations
    for(; i < n; ++i)
    {
        sum += data[i];
    }

    return sum / T(n);
}

template <typename InIt>
auto mean_and_variance_impl(InIt first, std::ptrdiff_t n)
    -> std::pair
    <
        typename std::iterator_traits<InIt>::value_type,
        typename std::iterator_traits<InIt>::value_type
    >
    requires std::same_as<typename std::iterator_traits<InIt>::value_type, float>
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr std::ptrdiff_t simd_elements = 256 / sizeof(T) / 8;
    T const* data = &*first;

    T const mean = mean_impl(first, n);
    __m256 vmean = _mm256_set1_ps(mean);
    __m256 vvariance_n = _mm256_setzero_ps();
    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256 values = _mm256_loadu_ps(&data[i]);
        values = _mm256_sub_ps(values, vmean);
        values = _mm256_mul_ps(values, values);
        vvariance_n = _mm256_add_ps(vvariance_n, values);
    }
    T variance_n = hsum_ps_avx(vvariance_n);

    // TODO unroll to prevent compiler optimizations
    for(; i < n; ++i)
    {
        T const value = data[i] - mean;
        variance_n += value * value;
    }

    return {mean, variance_n};
}

template <typename InIt>
auto mean_and_variance_impl(InIt first, std::ptrdiff_t n)
    -> std::pair
    <
        typename std::iterator_traits<InIt>::value_type,
        typename std::iterator_traits<InIt>::value_type
    >
    requires std::same_as<typename std::iterator_traits<InIt>::value_type, double>
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr std::ptrdiff_t simd_elements = 256 / sizeof(T) / 8;
    T const* data = &*first;

    T const mean = mean_impl(first, n);
    __m256d vmean = _mm256_set1_pd(mean);
    __m256d vvariance_n = _mm256_setzero_pd();
    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256d values = _mm256_loadu_pd(&data[i]);
        values = _mm256_sub_pd(values, vmean);
        values = _mm256_mul_pd(values, values);
        vvariance_n = _mm256_add_pd(vvariance_n, values);
    }
    T variance_n = hsum_pd_avx(vvariance_n);

    // TODO unroll to prevent compiler optimizations
    for(; i < n; ++i)
    {
        T const value = data[i] - mean;
        variance_n += value * value;
    }

    return {mean, variance_n};
}

} // namespace st::detail

#endif
