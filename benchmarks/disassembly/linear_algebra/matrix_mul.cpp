#include <simd_testbed/linear_algebra/matrix_cpp.hpp>
#include <simd_testbed/linear_algebra/matrix.hpp>

using matrix4x4f_cpp = st::cpp::basic_matrix<float, 4, 4>;
using matrix4x4f = st::basic_matrix<float, 4, 4>;
using matrix4x4_cpp = st::cpp::basic_matrix<double, 4, 4>;
using matrix4x4 = st::basic_matrix<double, 4, 4>;
using matrix3x3f_cpp = st::cpp::basic_matrix<float, 3, 3>;
using matrix3x3f = st::basic_matrix<float, 3, 3>;
using vector4f_cpp = st::cpp::basic_matrix<float, 4, 1>;
using vector4f = st::basic_matrix<float, 4, 1>;
using vector4_cpp = st::cpp::basic_matrix<double, 4, 1>;
using vector4 = st::basic_matrix<double, 4, 1>;
using vector3f_cpp = st::cpp::basic_matrix<float, 3, 1>;
using vector3f = st::basic_matrix<float, 3, 1>;

auto matrix4_matrxi4_mul_cpp(matrix4x4f_cpp const& lhs, matrix4x4f_cpp const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix4_matrxi4_mul(matrix4x4f const& lhs, matrix4x4f const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix4f_vec4f_mul_cpp(matrix4x4f_cpp const& lhs, vector4f_cpp const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix4f_vec4f_mul(matrix4x4f const& lhs, vector4f const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix4_vec4_mul_cpp(matrix4x4_cpp const& lhs, vector4_cpp const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix4_vec4_mul(matrix4x4 const& lhs, vector4 const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix3_vec3_mul_cpp(matrix3x3f_cpp const& lhs, vector3f_cpp const& rhs) noexcept
{
    return lhs * rhs;
}

auto matrix3_vec3_mul(matrix3x3f const& lhs, vector3f const& rhs) noexcept
{
    return lhs * rhs;
}
