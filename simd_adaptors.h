#ifndef SIMD_ADAPTORS_H
#define SIMD_ADAPTORS_H

#include "linalg.h"

#include <array>
#include <experimental/simd>

namespace stdx = std::experimental;

using Vec3_simd = std::array<stdx::native_simd<float>, 3>;

/* linalg adaptors */

namespace la {

namespace traits {

template <>
struct value_type<Vec3_simd> {
  using type = stdx::native_simd<float>;
};

template <>
struct dimension<Vec3_simd> {
  static constexpr std::size_t value = 3;
};

template <>
struct access<Vec3_simd, 0> { 
  static value_type_t<Vec3_simd>
  get(Vec3_simd const & vec) {
    return vec[0];
  }

  static void
  set(Vec3_simd & vec, value_type_t<Vec3_simd> scalar) {
    vec[0] = scalar;
  }
};

template <>
struct access<Vec3_simd, 1> {
  static value_type_t<Vec3_simd>
  get(Vec3_simd const & vec) {
    return vec[1];
  }

  static void
  set(Vec3_simd & vec, value_type_t<Vec3_simd> scalar) {
    vec[1] = scalar;
  }
};

template <>
struct access<Vec3_simd, 2> {
  static value_type_t<Vec3_simd>
  get(Vec3_simd const & vec) {
    return vec[2];
  }

  static void
  set(Vec3_simd & vec, value_type_t<Vec3_simd> scalar) {
    vec[2] = scalar;
  }
};

} // namespace traits

} // namespace la

#endif
