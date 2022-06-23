#include <simd_testbed/linear_algebra/matrix.hpp>

#include <catch2/catch_test_macros.hpp>

using matrix3x3f = st::basic_matrix<float, 3, 3>;
using matrix4x4f = st::basic_matrix<float, 4, 4>;
using matrix2x3 = st::basic_matrix<double, 2, 3>;
using matrix3x2 = st::basic_matrix<double, 3, 2>;
using matrix2x2 = st::basic_matrix<double, 2, 2>;
using matrix3x3 = st::basic_matrix<double, 3, 3>;

TEST_CASE("linear_algebra.matrix.operator==")
{
    auto const m1 = matrix4x4f
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = matrix4x4f
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };

    REQUIRE(m1 == m2);
}

TEST_CASE("linear_algebra.matrix.operator!=")
{
    auto const m1 = matrix4x4f
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = matrix4x4f{};

    REQUIRE(m1 != m2);
}

TEST_CASE("linear_algebra.matrix.operator* 4x4 * 4x4")
{
    auto const m1 = matrix4x4f
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = matrix4x4f
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m3_expected = matrix4x4f
    {
        56.0f, 62.0f, 68.0f, 74.0f,
        152.0f, 174.0f, 196.0f, 218.0f,
        248.0f, 286.0f, 324.0f, 362.0f,
        344.0f, 398.0f, 452.0f, 506.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEST_CASE("linear_algebra.matrix.operator* 3x3 * 3x3")
{
    auto const m1 = matrix3x3f
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f
    };
    auto const m2 = matrix3x3f
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f,
    };
    auto const m3_expected = matrix3x3f
    {
        20.0f, 23.0f, 26.0f,
        68.0f, 83.0f, 98.0f,
        116.0f, 143.0f, 170.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEST_CASE("linear_algebra.matrix.operator* 2x3 * 3x2")
{
    auto const m1 = matrix2x3
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m2 = matrix3x2
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m3_expected = matrix2x2
    {
        20.0, 23.0,
        68.0, 83.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEST_CASE("linear_algebra.matrix.operator* 3x2 * 2x3")
{
    auto const m1 = matrix3x2
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m2 = matrix2x3
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m3_expected = matrix3x3
    {
        4.0, 5.0, 6.0,
        20.0, 29.0, 38.0,
        36.0, 53.0, 70.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}
