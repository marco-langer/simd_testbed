#ifndef SIMD_TESTBED_ALGORITHM_DETAIL_MAX_VALUE_IMPL
#define SIMD_TESTBED_ALGORITHM_DETAIL_MAX_VALUE_IMPL

#include <immintrin.h>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <utility>

namespace st::detail {

template <typename InIt>
[[nodiscard]] constexpr auto
max_value(InIt first, InIt last)
    -> typename std::iterator_traits<InIt>::value_type
{
    assert(std::distance(first, last) > 0);

    auto max_value = *first++;
    for (; first != last; ++first)
    {
        if (*first > max_value)
        {
            max_value = *first;
        }
    }

    return max_value;
}

template <typename InIt>
[[nodiscard]] constexpr auto
min_value(InIt first, InIt last)
    -> typename std::iterator_traits<InIt>::value_type
{
    assert(std::distance(first, last) > 0);

    auto min_value = *first++;
    for (; first != last; ++first)
    {
        if (*first < min_value)
        {
            min_value = *first;
        }
    }

    return min_value;
}

template <typename InIt>
[[nodiscard]] constexpr auto
minmax_value(InIt first, InIt last)
    -> std::pair
    <
        typename std::iterator_traits<InIt>::value_type,
        typename std::iterator_traits<InIt>::value_type
    >
{
    assert(std::distance(first, last) > 0);
    using T = typename std::iterator_traits<InIt>::value_type;

    auto value = *first++;
    auto result = std::pair<T, T>{value, value};
    for (; first != last; ++first)
    {
        value = *first;
        if (value < result.first)
        {
            result.first = value;
        }
        if (value > result.second)
        {
            result.second = value;
        }
    }

    return result;
}

inline auto
max_value_avx_impl(std::uint8_t const* first, std::uint8_t const* last)
    -> std::uint8_t
{
    constexpr std::ptrdiff_t simd_elements = 16;

    const std::ptrdiff_t elements = std::distance(first, last);
    assert(elements > 0);

    __m128i max_values = _mm_setzero_si128();
    std::ptrdiff_t i = 0;
    for (; elements - i >= simd_elements; i += simd_elements)
    {
        __m128i values = _mm_loadu_si128(reinterpret_cast<const __m128i*>(first + i));
        max_values = _mm_max_epu8(values, max_values);
    }

    __m128i temp1, temp2, temp3, temp4;
    __m128i result1, result2, result3, result4;
    temp1 = _mm_srli_si128(max_values, 8);
    result1 = _mm_max_epu8(max_values, temp1);
    temp2 = _mm_srli_si128(result1, 4);
    result2 = _mm_max_epu8(result1, temp2);
    temp3 = _mm_srli_si128(result2, 2);
    result3 = _mm_max_epu8(result2, temp3);
    temp4 = _mm_srli_si128(result3, 1);
    result4 = _mm_max_epu8(result3, temp4);

    std::uint8_t result = static_cast<std::uint8_t>(_mm_extract_epi8(result4, 0));
    if (elements - i > 0)
    {
        return (std::max)(result, max_value(first + i, last));
    }
    else
    {
        return result;
    }
}

inline auto
max_value_avx_impl(std::int8_t const* first, std::int8_t const* last)
    -> std::int8_t
{
    constexpr std::ptrdiff_t simd_elements = 16;

    const auto elements = std::distance(first, last);
    assert(elements > 0);

    __m128i max_values = _mm_setzero_si128();
    std::ptrdiff_t i = 0;
    for (; elements - i >= simd_elements; i += simd_elements)
    {
        __m128i values = _mm_loadu_si128(reinterpret_cast<const __m128i*>(first + i));
        max_values = _mm_max_epi8(values, max_values);
    }

    __m128i temp1, temp2, temp3, temp4;
    __m128i result1, result2, result3, result4;
    temp1 = _mm_srli_si128(max_values, 8);
    result1 = _mm_max_epi8(max_values, temp1);
    temp2 = _mm_srli_si128(result1, 4);
    result2 = _mm_max_epi8(result1, temp2);
    temp3 = _mm_srli_si128(result2, 2);
    result3 = _mm_max_epi8(result2, temp3);
    temp4 = _mm_srli_si128(result3, 1);
    result4 = _mm_max_epi8(result3, temp4);

    std::int8_t result = static_cast<std::int8_t>(_mm_extract_epi8(result4, 0));
    if (elements - i > 0)
    {
        return (std::max)(result, max_value(first + i, last));
    }
    else
    {
        return result;
    }
}

inline auto
max_value_avx_impl(std::int16_t const* first, std::int16_t const* last)
    -> std::int16_t
{
    constexpr std::ptrdiff_t simd_elements = 8;

    const auto elements = std::distance(first, last);
    assert(elements > 0);

    __m128i max_values = _mm_setzero_si128();
    std::ptrdiff_t i = 0;
    for (; elements - i >= simd_elements; i += simd_elements)
    {
        __m128i values = _mm_loadu_si128(reinterpret_cast<const __m128i*>(first + i));
        max_values = _mm_max_epi16(values, max_values);
    }

    __m128i temp1, temp2, temp3;
    __m128i result1, result2, result3;
    temp1 = _mm_srli_si128(max_values, 4);
    result1 = _mm_max_epi16(max_values, temp1);
    temp2 = _mm_srli_si128(result1, 2);
    result2 = _mm_max_epi16(result1, temp2);
    temp3 = _mm_srli_si128(result2, 1);
    result3 = _mm_max_epi16(result2, temp3);

    std::int16_t result = static_cast<std::int16_t>(_mm_extract_epi16(result3, 0));
    if (elements - i > 0)
    {
        return (std::max)(result, max_value(first + i, last));
    }
    else
    {
        return result;
    }
}

inline auto
max_value_avx_impl(std::int32_t const* first, std::int32_t const* last)
    -> std::int32_t
{
    constexpr std::ptrdiff_t simd_elements = 8;

    const auto elements = std::distance(first, last);
    assert(elements > 0);

    __m128i max_values = _mm_setzero_si128();
    std::ptrdiff_t i = 0;
    for (; elements - i >= simd_elements; i += simd_elements)
    {
        __m128i values = _mm_loadu_si128(reinterpret_cast<const __m128i*>(first + i));
        max_values = _mm_max_epi32(values, max_values);
    }

    __m128i temp1, temp2;
    __m128i result1, result2;
    temp1 = _mm_srli_si128(max_values, 2);
    result1 = _mm_max_epi32(max_values, temp1);
    temp2 = _mm_srli_si128(result1, 1);
    result2 = _mm_max_epi32(result1, temp2);

    std::int32_t result = _mm_extract_epi32(result2, 0);
    if (elements - i > 0)
    {
        return (std::max)(result, max_value(first + i, last));
    }
    else
    {
        return result;
    }
}

} // namespace st::detail

#endif
