#include <simd_testbed/linear_algebra/matrix_cpp.hpp>
#include <simd_testbed/linear_algebra/matrix.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

using matrix3x3f_cpp = st::cpp::basic_matrix<float, 3, 3>;
using matrix4x4f_cpp = st::cpp::basic_matrix<float, 4, 4>;
using matrix2x3_cpp = st::cpp::basic_matrix<double, 2, 3>;
using matrix3x2_cpp = st::cpp::basic_matrix<double, 3, 2>;
using matrix2x2_cpp = st::cpp::basic_matrix<double, 2, 2>;
using matrix3x3_cpp = st::cpp::basic_matrix<double, 3, 3>;

using matrix3x3f = st::basic_matrix<float, 3, 3>;
using matrix4x4f = st::basic_matrix<float, 4, 4>;
using matrix2x3 = st::basic_matrix<double, 2, 3>;
using matrix3x2 = st::basic_matrix<double, 3, 2>;
using matrix2x2 = st::basic_matrix<double, 2, 2>;
using matrix3x3 = st::basic_matrix<double, 3, 3>;

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator==", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };

    REQUIRE(m1 == m2);
}


TEMPLATE_TEST_CASE("linear_algebra.matrix.operator==", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };

    REQUIRE(m1 == m2);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator!=", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 4, 4>{};

    REQUIRE(m1 != m2);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator!=", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::basic_matrix<TestType, 4, 4>{};

    REQUIRE(m1 != m2);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator* 4x4 * 4x4", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m3_expected = st::cpp::basic_matrix<TestType, 4, 4>
    {
        56.0f, 62.0f, 68.0f, 74.0f,
        152.0f, 174.0f, 196.0f, 218.0f,
        248.0f, 286.0f, 324.0f, 362.0f,
        344.0f, 398.0f, 452.0f, 506.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator* 4x4 * 4x4", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m2 = st::basic_matrix<TestType, 4, 4>
    {
        0.0f, 1.0f, 2.0f, 3.0f,
        4.0f, 5.0f, 6.0f, 7.0f,
        8.0f, 9.0f, 10.0f, 11.0f,
        12.0f, 13.0f, 14.0f, 15.0f
    };
    auto const m3_expected = st::basic_matrix<TestType, 4, 4>
    {
        56.0f, 62.0f, 68.0f, 74.0f,
        152.0f, 174.0f, 196.0f, 218.0f,
        248.0f, 286.0f, 324.0f, 362.0f,
        344.0f, 398.0f, 452.0f, 506.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator* 3x3 * 3x3", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 3, 3>
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 3, 3>
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f,
    };
    auto const m3_expected = st::cpp::basic_matrix<TestType, 3, 3>
    {
        20.0f, 23.0f, 26.0f,
        68.0f, 83.0f, 98.0f,
        116.0f, 143.0f, 170.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator* 3x3 * 3x3", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 3, 3>
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f
    };
    auto const m2 = st::basic_matrix<TestType, 3, 3>
    {
        0.0f, 1.0f, 2.0f,
        4.0f, 5.0f, 6.0f,
        8.0f, 9.0f, 10.0f,
    };
    auto const m3_expected = st::basic_matrix<TestType, 3, 3>
    {
        20.0f, 23.0f, 26.0f,
        68.0f, 83.0f, 98.0f,
        116.0f, 143.0f, 170.0f
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator* 2x3 * 3x2", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 2, 3>
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 3, 2>
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m3_expected = st::cpp::basic_matrix<TestType, 2, 2>
    {
        20.0, 23.0,
        68.0, 83.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator* 2x3 * 3x2", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 2, 3>
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m2 = st::basic_matrix<TestType, 3, 2>
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m3_expected = st::basic_matrix<TestType, 2, 2>
    {
        20.0, 23.0,
        68.0, 83.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator* 3x2 * 2x3", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 3, 2>
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 2, 3>
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m3_expected = st::cpp::basic_matrix<TestType, 3, 3>
    {
        4.0, 5.0, 6.0,
        20.0, 29.0, 38.0,
        36.0, 53.0, 70.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator* 3x2 * 2x3", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 3, 2>
    {
        0.0, 1.0,
        4.0, 5.0,
        8.0, 9.0
    };
    auto const m2 = st::basic_matrix<TestType, 2, 3>
    {
        0.0, 1.0, 2.0,
        4.0, 5.0, 6.0
    };
    auto const m3_expected = st::basic_matrix<TestType, 3, 3>
    {
        4.0, 5.0, 6.0,
        20.0, 29.0, 38.0,
        36.0, 53.0, 70.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix_cpp.operator* 5x6 * 6x5", "", float, double)
{
    auto const m1 = st::cpp::basic_matrix<TestType, 5, 6>
    {
        0.0, 1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0, 9.0,
        10.0, 11.0, 12.0, 13.0, 14.0,
        15.0, 16.0, 17.0, 18.0, 19.0,
        20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0
    };
    auto const m2 = st::cpp::basic_matrix<TestType, 6, 5>
    {
        1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
        7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0
    };
    auto const m3_expected = st::cpp::basic_matrix<TestType, 5, 5>
    {
        290.0, 305.0, 320.0, 335.0, 350.0,
        776.0, 827.0, 878.0, 929.0, 980.0,
        1262.0, 1349.0, 1436.0, 1523.0, 1610.0,
        1748.0, 1871.0, 1994.0, 2117.0, 2240.0,
        2234.0, 2393.0, 2552.0, 2711.0, 2870.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}

TEMPLATE_TEST_CASE("linear_algebra.matrix.operator* 5x6 * 6x5", "", float, double)
{
    auto const m1 = st::basic_matrix<TestType, 5, 6>
    {
        0.0, 1.0, 2.0, 3.0, 4.0,
        5.0, 6.0, 7.0, 8.0, 9.0,
        10.0, 11.0, 12.0, 13.0, 14.0,
        15.0, 16.0, 17.0, 18.0, 19.0,
        20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0
    };
    auto const m2 = st::basic_matrix<TestType, 6, 5>
    {
        1.0, 2.0, 3.0, 4.0, 5.0, 6.0,
        7.0, 8.0, 9.0, 10.0, 11.0, 12.0,
        13.0, 14.0, 15.0, 16.0, 17.0, 18.0,
        19.0, 20.0, 21.0, 22.0, 23.0, 24.0,
        25.0, 26.0, 27.0, 28.0, 29.0, 30.0
    };
    auto const m3_expected = st::basic_matrix<TestType, 5, 5>
    {
        290.0, 305.0, 320.0, 335.0, 350.0,
        776.0, 827.0, 878.0, 929.0, 980.0,
        1262.0, 1349.0, 1436.0, 1523.0, 1610.0,
        1748.0, 1871.0, 1994.0, 2117.0, 2240.0,
        2234.0, 2393.0, 2552.0, 2711.0, 2870.0
    };

    auto const m3 = m1 * m2;

    REQUIRE(m3 == m3_expected);
}
