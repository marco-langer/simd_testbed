#include "naive_adaptors.hpp"
#include "simd_adaptors.hpp"

float
dot_product_naive(Vec3 const & lhs, Vec3 const & rhs) {
  return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

float
la_dot_product_naive(Vec3 const & lhs, Vec3 const & rhs) {
  return la::dot_product(lhs, rhs);
}

stdx::native_simd<float>
dot_product_std_simd(Vec3_simd const & lhs, Vec3_simd const & rhs) {
  return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

stdx::native_simd<float>
la_dot_product_std_simd(Vec3_simd const & lhs, Vec3_simd const & rhs) {
  return la::dot_product(lhs, rhs);
}

