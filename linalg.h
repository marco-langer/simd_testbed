#ifndef LINALG_H
#define LINALG_H

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
static constexpr std::size_t dimension_v = dimension<T>::value;

template <typename T, std::size_t I>
struct access;

} // namespace traits

template <typename T, std::size_t I>
traits::value_type_t<T>
get(T const & t) {
  return traits::access<T, I>::get(t);
}

template <typename T, std::size_t I>
void
set(T & t, traits::value_type_t<T> scalar) {
  traits::access<T, I>::set(t, scalar);
}

/* algorithms */

namespace detail {

template <typename T, std::size_t... I>
void
add_impl(T & result, T const & lhs, T const & rhs, std::index_sequence<I...>) {
  (..., set<T, I>(result, get<T, I>(lhs) + get<T, I>(rhs)));
}

template <typename T, std::size_t... I>
traits::value_type_t<T>
dot_product_impl(T const & lhs, T const & rhs, std::index_sequence<I...>) {
  return (... + (get<T, I>(lhs) * get<T, I>(rhs)));
}

} // namespace detail

template <typename T>
T
operator+(T const & lhs, T const & rhs) {
  T result;
  detail::add_impl(result, lhs, rhs, std::make_index_sequence<la::traits::dimension_v<T>>{});
  return result;
}

template <typename T>
traits::value_type_t<T>
dot_product(T const & lhs, T const & rhs) {
  return detail::dot_product_impl(lhs, rhs, std::make_index_sequence<la::traits::dimension_v<T>>{});
}

} // namespace la

#endif
