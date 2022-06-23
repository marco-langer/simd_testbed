#ifndef SIMD_TESTBED_NUMERIC_ADD_SATURATED_HPP
#define SIMD_TESTBED_NUMERIC_ADD_SATURATED_HPP

#include <simd_testbed/numeric/detail/add_saturated_impl.hpp>

#include <simd_testbed/traits.hpp>

#include <concepts>
#include <iterator>
#include <type_traits>

namespace st {

template <standard_arithmetic T, std::input_iterator InIt>
constexpr void add(InIt first, InIt last, T c)
{
    for (; first != last; ++first)
    {
        *first += c;
    }
}

template <standard_integer T, std::input_iterator InIt>
constexpr void add_saturated(InIt first, InIt last, T c)
    requires (std::is_same_v<typename std::iterator_traits<InIt>::value_type, T>)
{
    detail::add_saturated_impl(first, last, c);
}

template <standard_unsigned_integer T, std::input_iterator InIt>
constexpr void add_saturated_branchless(InIt first, InIt last, T c)
    requires (std::is_same_v<typename std::iterator_traits<InIt>::value_type, T>)
{
    detail::add_saturated_branchless_impl(first, last, c);
}

template <standard_integer T, std::contiguous_iterator InIt>
void add_saturated_intrin(InIt first, InIt last, T c)
    requires (sizeof(T) < 4
        && std::is_same_v<typename std::iterator_traits<InIt>::value_type, T>)
{
    auto const n = std::distance(first, last);
    detail::add_saturated_avx2_impl(&*first, n, c);
}

} // namespace st

#endif
