#ifndef SIMD_TESTBED_STATISTICS_MEAN_CPP_HPP
#define SIMD_TESTBED_STATISTICS_MEAN_CPP_HPP

#include <algorithm>
#include <iterator>
#include <numeric>

namespace st::cpp {

template <typename InIt, typename T = typename std::iterator_traits<InIt>::value_type>
auto mean_stl(InIt first, InIt last) -> T
{
    auto const n = std::distance(first, last);
    if (n == 0)
    {
        return T{};
    }
    else
    {
        return std::accumulate(first, last, T{}) / T(n);
    }
}

template <typename InIt, typename T = typename std::iterator_traits<InIt>::value_type>
auto mean(InIt first, InIt last) -> T
{
    auto const n = std::distance(first, last);
    if (n == 0)
    {
        return T{};
    }
    else
    {
        auto sum = T{};
        for (; first != last; ++first)
        {
            sum += *first;
        }
        return sum / T(n);
    }
}

} // namespace st

#endif
