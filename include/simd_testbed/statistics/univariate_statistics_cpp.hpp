#ifndef SIMD_TESTBED_STATISTICS_UNIVARIATE_STATISTICS_CPP_HPP
#define SIMD_TESTBED_STATISTICS_UNIVARIATE_STATISTICS_CPP_HPP

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <type_traits>
#include <utility>

namespace st::cpp {

// naive textbook solution for calculation the mean value of a range using STL
template
<
    typename InIt,
    typename T =  std::conditional_t
    <
        std::is_floating_point_v<typename std::iterator_traits<InIt>::value_type>,
        typename std::iterator_traits<InIt>::value_type,
        double
    >
>
[[nodiscard]] constexpr auto mean_stl(InIt first, InIt last) -> T
{
    auto const n = std::distance(first, last);
    assert(n > 1);

    return std::accumulate(first, last, T{}) / T(n);
}

// naive textbook solution for calculation the mean value of a range
template
<
    typename InIt,
    typename T =  std::conditional_t
    <
        std::is_floating_point_v<typename std::iterator_traits<InIt>::value_type>,
        typename std::iterator_traits<InIt>::value_type,
        double
    >
>
[[nodiscard]] constexpr auto mean(InIt first, InIt last) -> T
{
    auto const n = std::distance(first, last);
    assert(n > 1);

    auto sum = T{};
    for (; first != last; ++first)
    {
        sum += *first;
    }
    return sum / T(n);
}

// naive textbook solution for calculation for calculating the mean and sample variance of a range
template
<
    typename InIt,
    typename T =  std::conditional_t
    <
        std::is_floating_point_v<typename std::iterator_traits<InIt>::value_type>,
        typename std::iterator_traits<InIt>::value_type,
        double
    >
>
[[nodiscard]] auto mean_and_sample_variance(InIt first, InIt last) -> std::pair<T, T>
{
    auto const n = std::distance(first, last);
    assert(n > 1);

    auto const m = mean(first, last);
    auto variance_n = T{};
    for (; first != last; ++first)
    {
        auto value = *first - m;
        variance_n += value * value;
    }
    return {m, variance_n / T(n)};
}

} // namespace st

#endif
