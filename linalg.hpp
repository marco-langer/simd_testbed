#ifndef LINALG_HPP
#define LINALG_HPP

#include <utility>

namespace la {

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

template <typename T, std::size_t I>
constexpr traits::value_type_t<T>
get(T const & t)
{
  return traits::access<T, I>::get(t);
}

template <typename T, std::size_t I>
constexpr void
set(T & t, traits::value_type_t<T> scalar)
{
  traits::access<T, I>::set(t, scalar);
}

/* algorithms */

template <typename T>
constexpr T
operator+(T const & lhs, T const & rhs)
{
  T result;
  auto add_helper = [&]<std::size_t... I>(std::index_sequence<I...>)
  {
    (..., set<T, I>(result, get<T, I>(lhs) + get<T, I>(rhs)));
  };
  add_helper(std::make_index_sequence<la::traits::dimension_v<T>>{});
  return result;
}

template <typename T>
constexpr traits::value_type_t<T>
dot_product(T const & lhs, T const & rhs)
{
  auto dot_product_helper = [&]<std::size_t... I>(std::index_sequence<I...>)
  {
    return (... + (get<T, I>(lhs) * get<T, I>(rhs)));
  };
  return dot_product_helper(std::make_index_sequence<la::traits::dimension_v<T>>{});
}

} // namespace la

#endif
