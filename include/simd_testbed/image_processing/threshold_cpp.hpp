#ifndef SIMD_TESTBED_IMAGE_PROCESSING_THRESHOLD_CPP_HPP
#define SIMD_TESTBED_IMAGE_PROCESSING_THRESHOLD_CPP_HPP

#include <simd_testbed/traits.hpp>

#include <iterator>
#include <limits>
#include <type_traits>

namespace st::cpp {

struct threshold_binary{};
struct threshold_binary_inverse{};
struct threshold_truncate{};
struct threshold_to_zero{};
struct threshold_to_zero_inverse{};

template <typename T>
concept threshold = detail::is_one_of
<
    T,
    threshold_binary,
    threshold_binary_inverse,
    threshold_truncate,
    threshold_to_zero,
    threshold_to_zero_inverse
>;

namespace detail {

template <typename InIt, typename OutIt>
void apply_threshold_binary(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value)
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr T min = std::numeric_limits<T>::min();
    constexpr T max = std::numeric_limits<T>::max();

    for (; first != last; ++first, ++d_first)
    {
        T const value = *first;
        if (value > threshold_value)
        {
            *d_first = max;
        }
        else
        {
            *d_first = min;
        }
    }
}

template <typename InIt, typename OutIt>
void apply_threshold_binary_inverse(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value)
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr T min = std::numeric_limits<T>::min();
    constexpr T max = std::numeric_limits<T>::max();

    for (; first != last; ++first, ++d_first)
    {
        T const value = *first;
        if (value > threshold_value)
        {
            *d_first = min;
        }
        else
        {
            *d_first = max;
        }
    }
}

template <typename InIt, typename OutIt>
void apply_threshold_truncate(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value)
{
    using T = typename std::iterator_traits<InIt>::value_type;

    for (; first != last; ++first, ++d_first)
    {
        T const value = *first;
        if (value > threshold_value)
        {
            *d_first = threshold_value;
        }
        else
        {
            *d_first = value;
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

} // namespace detail

template <typename InIt, typename OutIt, threshold Threshold>
void apply_threshold(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value, Threshold)
{
    if constexpr (std::is_same_v<Threshold, threshold_binary>)
    {
        detail::apply_threshold_binary(first, last, d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_binary_inverse>)
    {
        detail::apply_threshold_binary_inverse(first, last, d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_truncate>)
    {
        detail::apply_threshold_truncate(first, last, d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_to_zero>)
    {
        detail::apply_threshold_to_zero(first, last, d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_to_zero_inverse>)
    {
        detail::apply_threshold_to_zero_inverse(first, last, d_first, threshold_value);
    }
}

} // namespace st::cpp

#endif
