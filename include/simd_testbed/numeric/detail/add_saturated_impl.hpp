#ifndef SIMD_TESTBED_NUMERIC_DETAIL_ADD_SATURATED_HPP
#define SIMD_TESTBED_NUMERIC_DETAIL_ADD_SATURATED_HPP

#include <simd_testbed/traits.hpp>

#include <immintrin.h>

#include <cstdint>
#include <iterator>
#include <limits>
#include <type_traits>

namespace st::detail {

template <standard_integer T, std::input_iterator InIt>
constexpr void add_saturated_impl(InIt first, InIt last, T c)
    requires (std::is_same_v<typename std::iterator_traits<InIt>::value_type, T>)
{
    constexpr auto max = std::numeric_limits<T>::max();

    if constexpr (std::is_unsigned_v<T>)
    {
        for (; first != last; ++first)
        {
            auto const value = *first;
            if (max - c < value)
            {
                *first = max;
            }
            else
            {
                *first += c;
            }
        }
    }
    else
    {
        constexpr auto min = std::numeric_limits<T>::min();

        if (c >= T{})
        {
            for (; first != last; ++first)
            {
                auto const value = *first;
                if (max - c < value)
                {
                    *first = max;
                }
                else
                {
                    *first += c;
                }
            }
        }
        else
        {
            for (; first != last; ++first)
            {
                auto const value = *first;
                if (min - c > value)
                {
                    *first = min;
                }
                else
                {
                    *first += c;
                }
            }
        }
    }
}

template <standard_unsigned_integer T, std::input_iterator InIt>
constexpr void add_saturated_branchless_impl(InIt first, InIt last, T c)
    requires (std::is_same_v<typename std::iterator_traits<InIt>::value_type, T>)
{
    /**
     * Taken from http://locklessinc.com/articles/sat_arithmetic/
     * which is also listed as a implementation reference for P0543
     * (attempt to add saturation arithmetic to C++26)
     */
    for (; first != last; ++first)
    {
        T const x = *first;
        T result = x + c;
        result |= static_cast<T>(-(result < x));
        *first = result;
    }
}

inline void add_saturated_avx2_impl(std::uint8_t* first, std::ptrdiff_t n, std::uint8_t c)
{
    constexpr auto simd_elements = 32;

    // TODO is there a better way of setting an uint_8?
    __m256i f_ui8x32 = _mm256_set1_epi8(0x40);
    __m256i c_ui8x32 = _mm256_set1_epi8(static_cast<char>(c - 0x80));
    c_ui8x32 = _mm256_add_epi8(c_ui8x32, f_ui8x32);
    c_ui8x32 = _mm256_add_epi8(c_ui8x32, f_ui8x32);

    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals_ui8x32 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(first + i));
        __m256i result_ui8x32 = _mm256_adds_epu8(vals_ui8x32, c_ui8x32);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(first + i), result_ui8x32);
    }

    add_saturated_impl(first + i , first + n, c);
}

inline void add_saturated_avx2_impl(std::uint16_t* first, std::ptrdiff_t n, std::uint16_t c)
{
    constexpr auto simd_elements = 16;

    // TODO is there a better way of setting an uint_16?
    __m256i f_ui16x16 = _mm256_set1_epi16(0x4000);
    __m256i c_ui16x16 = _mm256_set1_epi16(static_cast<short>(c - 0x8000));
    c_ui16x16 = _mm256_add_epi16(c_ui16x16, f_ui16x16);
    c_ui16x16 = _mm256_add_epi16(c_ui16x16, f_ui16x16);

    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals_ui16x16 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(first + i));
        __m256i result_ui16x16 = _mm256_adds_epu16(vals_ui16x16, c_ui16x16);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(first + i), result_ui16x16);
    }

    add_saturated_impl(first + i , first + n, c);
}

inline void add_saturated_avx2_impl(std::int8_t* first, std::ptrdiff_t n, std::int8_t c)
{
    constexpr auto simd_elements = 32;
    __m256i c_i8x32 = _mm256_set1_epi8(c);

    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals_i8x32 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(first + i));
        __m256i result_i8x32 = _mm256_adds_epi8(vals_i8x32, c_i8x32);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(first + i), result_i8x32);
    }

    add_saturated_impl(first + i , first + n, c);
}

inline void add_saturated_avx2_impl(std::int16_t* first, std::ptrdiff_t n, std::int16_t c)
{
    constexpr auto simd_elements = 16;
    __m256i c_i16x16 = _mm256_set1_epi16(c);

    std::ptrdiff_t i = 0;
    for (; n - i >= simd_elements; i += simd_elements)
    {
        __m256i vals_i16x16 = _mm256_loadu_si256(reinterpret_cast<__m256i*>(first + i));
        __m256i result_i16x16 = _mm256_adds_epi16(vals_i16x16, c_i16x16);
        _mm256_storeu_si256(reinterpret_cast<__m256i*>(first + i), result_i16x16);
    }

    add_saturated_impl(first + i , first + n, c);
}

} // namespace st::detail

#endif
