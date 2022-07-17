#ifndef SIMD_TESTBED_STATISTICS_UNIVARIATE_STATISTICS_HPP
#define SIMD_TESTBED_STATISTICS_UNIVARIATE_STATISTICS_HPP

#include <simd_testbed/statistics/detail/univariate_statistics_impl.hpp>
#include <simd_testbed/traits.hpp>

#include <cassert>
#include <concepts>
#include <iterator>
#include <utility>

namespace st {

// naive textbook solution for calculation for calculating the mean of a range
// using AVX2 intrinsics
template <typename InIt>
[[nodiscard]] auto mean(InIt first, InIt last)
    -> typename std::iterator_traits<InIt>::value_type
    requires detail::is_one_of<typename std::iterator_traits<InIt>::value_type, float, double>
{
    auto const n = std::distance(first, last);
    assert(n > 1);
    return detail::mean_impl(first, n);
}

// naive textbook solution for calculation for calculating the mean and sample variance
// of a range using AVX2 intrinsics
template <typename InIt>
[[nodiscard]] auto mean_and_sample_variance(InIt first, InIt last)
    -> std::pair
    <
        typename std::iterator_traits<InIt>::value_type,
        typename std::iterator_traits<InIt>::value_type
    >
    requires detail::is_one_of<typename std::iterator_traits<InIt>::value_type, float, double>
{
    using T = typename std::iterator_traits<InIt>::value_type;
    auto const n = std::distance(first, last);
    assert(n > 1);

    auto const [mean, variance_n] = detail::mean_and_variance_impl(first, n);
    return {mean, variance_n / T(n)};
}

// TODO implement AVX2 version of boost::math::statistics::mean_and_sample_variance

} // namespace st

#endif
