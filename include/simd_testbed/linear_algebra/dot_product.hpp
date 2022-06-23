#ifndef SIMD_TESTBED_DOT_PRODUCT_HPP
#define SIMD_TESTBED_DOT_PRODUCT_HPP

#include <utility>

namespace st {

namespace traits {

/* adaptors */

template <typename T>
struct value_type;

template <typename T>
using value_type_t = typename value_type<T>::type;

template <typename T>
struct dimension;

template <typename T>
inline constexpr std::size_t dimension_v = dimension<T>::value;

template <typename T, std::size_t I>
struct access;

} // namespace traits

// dot product implementation

template <typename T, std::size_t I>
[[nodiscard]] constexpr traits::value_type_t<T>
get(T const& t)
{
    return traits::access<T, I>::get(t);
}

template <typename T, std::size_t I>
constexpr void
set(T& t, traits::value_type_t<T> scalar)
{
    traits::access<T, I>::set(t, scalar);
}

template <typename T>
[[nodiscard]] constexpr T
operator+(T const& lhs, T const& rhs) noexcept
{
    T result;
    auto add_helper = [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        (..., set<T, I>(result, get<T, I>(lhs) + get<T, I>(rhs)));
    };
    add_helper(std::make_index_sequence<traits::dimension_v<T>>{});
    return result;
}

template <typename T>
[[nodiscard]] constexpr traits::value_type_t<T>
dot_product(T const& lhs, T const& rhs) noexcept
{
    return [&]<std::size_t... I>(std::index_sequence<I...>)
    {
        return (... + (get<T, I>(lhs) * get<T, I>(rhs)));
    }(std::make_index_sequence<traits::dimension_v<T>>{});
}

} // namespace st

#endif
