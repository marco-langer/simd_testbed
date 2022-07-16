#ifndef SIMD_TESTBED_STATISTICS_MEAN_HPP
#define SIMD_TESTBED_STATISTICS_MEAN_HPP

#include <simd_testbed/statistics/detail/univariate_statistics_impl.hpp>
#include <simd_testbed/traits.hpp>

#include <concepts>
#include <iterator>

namespace st {

template <typename InIt>
auto mean(InIt first, InIt last) -> typename std::iterator_traits<InIt>::value_type
    requires std::floating_point<typename std::iterator_traits<InIt>::value_type>
{
    return detail::mean_impl(first, last);
}

} // namespace st

#endif
