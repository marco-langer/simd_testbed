#ifndef SIMD_TESTBED_IMAGE_PROCESSING_DETAIL_THRESHOLD_IMPL_HPP
#define SIMD_TESTBED_IMAGE_PROCESSING_DETAIL_THRESHOLD_IMPL_HPP

#include <cstdint>
#include <immintrin.h>
#include <iterator>
#include <limits>

namespace st::detail {

inline void apply_threshold_binary(
    std::uint8_t const* first, std::ptrdiff_t n, std::uint8_t* d_first,
    std::uint8_t threshold_value)
{
    constexpr auto min = std::numeric_limits<std::uint8_t>::min();
    constexpr auto max = std::numeric_limits<std::uint8_t>::max();
    constexpr auto simd_elements = 32;

    __m256i vpixel_sf = _mm256_set1_epi8(static_cast<char>(0x80));
    __m256i vmin = _mm256_setzero_si256();
    __m256i vmax = _mm256_set1_epi8(static_cast<char>(255));
    __m256i vthreshold = _mm256_set1_epi8(static_cast<char>(threshold_value));
    __m256i vthreshold2 = _mm256_sub_epi8(vthreshold, vpixel_sf);

    std::ptrdiff_t i = 0;
    for(; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(&first[i]));
        __m256i vals2 = _mm256_sub_epi8(vals, vpixel_sf);
        __m256i vmask = _mm256_cmpgt_epi8(vals2, vthreshold2);
        __m256i vresult = _mm256_blendv_epi8(vmin, vmax, vmask);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(&d_first[i]), vresult);
    }

    for (; i < n; ++i)
    {
        auto const value = first[i];
        if (value > threshold_value)
        {
            d_first[i] = max;
        }
        else
        {
            d_first[i] = min;
        }
    }
}

inline void apply_threshold_binary_inverse(
    std::uint8_t const* first, std::ptrdiff_t n, std::uint8_t* d_first,
    std::uint8_t threshold_value)
{
    constexpr auto min = std::numeric_limits<std::uint8_t>::min();
    constexpr auto max = std::numeric_limits<std::uint8_t>::max();
    constexpr auto simd_elements = 32;

    __m256i vmin = _mm256_setzero_si256();
    __m256i vmax = _mm256_set1_epi8(static_cast<char>(255));
    __m256i vthreshold = _mm256_set1_epi8(static_cast<char>(threshold_value));

    std::ptrdiff_t i = 0;
    for(; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(&first[i]));
        __m256i vmask = _mm256_cmpgt_epi8(vals, vthreshold);
        __m256i vresult = _mm256_blendv_epi8(vmax, vmin, vmask);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(&d_first[i]), vresult);
    }

    for (; i < n; ++i)
    {
        auto const value = first[i];
        if (value > threshold_value)
        {
            d_first[i] = min;
        }
        else
        {
            d_first[i] = max;
        }
    }
}

inline void apply_threshold_truncate(
    std::uint8_t const* first, std::ptrdiff_t n, std::uint8_t* d_first,
    std::uint8_t threshold_value)
{
    constexpr auto simd_elements = 32;

    __m256i vthreshold = _mm256_set1_epi8(static_cast<char>(threshold_value));

    std::ptrdiff_t i = 0;
    for(; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals = _mm256_loadu_si256(reinterpret_cast<__m256i const*>(&first[i]));
        __m256i vmask = _mm256_cmpgt_epi8(vals, vthreshold);
        __m256i vresult = _mm256_blendv_epi8(vthreshold, vals, vmask);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(&d_first[i]), vresult);
    }

    for (; i < n; ++i)
    {
        auto const value = first[i];
        if (value > threshold_value)
        {
            d_first[i] = threshold_value;
        }
        else
        {
            d_first[i] = value;
        }
    }
}

template <typename InIt, typename OutIt>
void apply_threshold_to_zero(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value)
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr T min = std::numeric_limits<T>::min();

    for (; first != last; ++first, ++d_first)
    {
        T const value = *first;
        if (value > threshold_value)
        {
            *d_first = value;
        }
        else
        {
            *d_first = min;
        }
    }
}


template <typename InIt, typename OutIt>
void apply_threshold_to_zero_inverse(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value)
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr T min = std::numeric_limits<T>::min();

    for (; first != last; ++first, ++d_first)
    {
        T const value = *first;
        if (value > threshold_value)
        {
            *d_first = min;
        }
        else
        {
            *d_first = value;
        }
    }
}

} // namespace st::detail

#endif
