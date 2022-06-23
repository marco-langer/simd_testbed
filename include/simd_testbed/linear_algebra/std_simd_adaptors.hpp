#ifndef SIMD_TESTBED_STD_SIMD_ADAPTORS_HPP
#define SIMD_TESTBED_STD_SIMD_ADAPTORS_HPP

#include <simd_testbed/linear_algebra/dot_product.hpp>

#include <array>
#include <experimental/simd>

namespace stdx = std::experimental;

using vec3_simd = std::array<stdx::native_simd<float>, 3>;

/* linalg adaptors */

namespace st::traits {

template <>
struct value_type<vec3_simd>
{
    using type = typename vec3_simd::value_type;
};

template <>
struct dimension<vec3_simd>
{
    static constexpr std::size_t value = 3;
};

template <>
struct access<vec3_simd, 0>
{
    static value_type_t<vec3_simd>
    get(vec3_simd const& vec)
    {
        return vec[0];
    }

    static void
    set(vec3_simd& vec, value_type_t<vec3_simd> scalar)
    {
        vec[0] = scalar;
    }
};

template <>
struct access<vec3_simd, 1>
{
    static value_type_t<vec3_simd>
    get(vec3_simd const& vec)
    {
        return vec[1];
    }

    static void
    set(vec3_simd& vec, value_type_t<vec3_simd> scalar)
    {
        vec[1] = scalar;
    }
};

template <>
struct access<vec3_simd, 2>
{
    static value_type_t<vec3_simd>
    get(vec3_simd const& vec)
    {
        return vec[2];
    }

    static void
    set(vec3_simd& vec, value_type_t<vec3_simd> scalar)
    {
        vec[2] = scalar;
    }
};

} // namespace st::traits

#endif
