#include <simd_testbed/linear_algebra/naive_adaptors.hpp>
#include <simd_testbed/linear_algebra/std_simd_adaptors.hpp>

float
dot_product_naive(vec3 const& lhs, vec3 const& rhs)
{
  return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

float
la_dot_product_naive(vec3 const& lhs, vec3 const& rhs)
{
    return st::dot_product(lhs, rhs);
}

stdx::native_simd<float>
dot_product_std_simd(vec3_simd const& lhs, vec3_simd const& rhs)
{
    return lhs[0] * rhs[0] + lhs[1] * rhs[1] + lhs[2] * rhs[2];
}

stdx::native_simd<float>
la_dot_product_std_simd(vec3_simd const& lhs, vec3_simd const& rhs)
{
    return st::dot_product(lhs, rhs);
}
