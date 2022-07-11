#ifndef SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_TRAITS_HPP
#define SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_TRAITS_HPP

#include <type_traits>

namespace st {

template <typename T>
struct is_matrix : std::false_type {};

template <typename T>
concept matrix = is_matrix<T>::value;

template <typename T>
concept square_matrix = matrix<T> && (T::cols % 2 == 0);

} // namespace st

#endif
