#ifndef SIMD_TESTBED_NAIVE_ADAPTORS_HPP
#define SIMD_TESTBED_NAIVE_ADAPTORS_HPP

#include <simd_testbed/linear_algebra/dot_product.hpp>

#include <array>

using vec3 = std::array<float, 3>;

/* linalg adaptors */

namespace st::traits {

template <>
struct value_type<vec3>
{
    using type = typename vec3::value_type;
};

template <>
struct dimension<vec3>
{
    static constexpr std::size_t value = 3;
};

template <>
struct access<vec3, 0>
{
    static value_type_t<vec3>
    get(vec3 const& vec)
    {
        return vec[0];
    }

    static void
    set(vec3& vec, value_type_t<vec3> scalar)
    {
        vec[0] = scalar;
    }
};

template <>
struct access<vec3, 1>
{
    static value_type_t<vec3>
    get(vec3 const& vec)
    {
        return vec[1];
    }

    static void
    set(vec3& vec, value_type_t<vec3> scalar)
    {
        vec[1] = scalar;
    }
};

template <>
struct access<vec3, 2>
{
    static value_type_t<vec3>
    get(vec3 const& vec)
    {
        return vec[2];
    }

    static void
    set(vec3& vec, value_type_t<vec3> scalar)
    {
        vec[2] = scalar;
    }
};

} // namespace st::traits

#endif
