#ifndef SIMD_TESTBED_ALGORITHM_ALGORITHM
#define SIMD_TESTBED_ALGORITHM_ALGORITHM

#include <simd_testbed/algorithm/detail/minmax_value_impl.hpp>
#include <simd_testbed/algorithm/traits.hpp>

#include <iterator>

namespace st {

template <std::contiguous_iterator InIt, std::sentinel_for<InIt> S>
    requires is_standard_arithmetic_v<typename InIt::value_type>
[[nodiscard]] auto
max_value_avx(InIt first, S last)
    -> typename std::iterator_traits<InIt>::value_type
{
    using T = typename std::iterator_traits<InIt>::value_type;
    constexpr bool is_64bit_integer =
        !std::is_floating_point_v<T> && sizeof(T) == 8;

    if constexpr (is_64bit_integer)
    {
        return detail::max_value(first, last);
    }
    else
    {
        return detail::max_value_avx_impl(&*first, &*last);
    }
}

template <std::contiguous_iterator InIt, std::sentinel_for<InIt> S>
    requires is_standard_arithmetic_v<typename InIt::value_type>
[[nodiscard]] auto
max_value(InIt first, S last)
    -> typename std::iterator_traits<InIt>::value_type
{
    return max_value_avx(first, last);
}

} // namespace st

#endif
