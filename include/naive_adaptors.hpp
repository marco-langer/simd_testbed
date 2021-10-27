#ifndef NAIVE_ADAPTORS_HPP
#define NAIVE_ADAPTORS_HPP

#include "linalg.hpp"

#include <array>

using Vec3 = std::array<float, 3>;

/* linalg adaptors */

namespace la::traits {

template <>
struct value_type<Vec3> {
  using type = float;
};

template <>
struct dimension<Vec3> {
  static constexpr std::size_t value = 3;
};

template <>
struct access<Vec3, 0> { 
  static value_type_t<Vec3>
  get(Vec3 const & vec) {
    return vec[0];
  }

  static void
  set(Vec3 & vec, value_type_t<Vec3> scalar) {
    vec[0] = scalar;
  }
};

template <>
struct access<Vec3, 1> {
  static value_type_t<Vec3>
  get(Vec3 const & vec) {
    return vec[1];
  }

  static void
  set(Vec3 & vec, value_type_t<Vec3> scalar) {
    vec[1] = scalar;
  }
};

template <>
struct access<Vec3, 2> {
  static value_type_t<Vec3>
  get(Vec3 const & vec) {
    return vec[2];
  }

  static void
  set(Vec3 & vec, value_type_t<Vec3> scalar) {
    vec[2] = scalar;
  }
};

} // namespace la::traits

#endif
