#include <simd_testbed/statistics/univariate_statistics_cpp.hpp>
#include <simd_testbed/statistics/univariate_statistics.hpp>

#include <boost/math/statistics/univariate_statistics.hpp>
#include <catch2/catch_approx.hpp>
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <cmath>
#include <cstdint>
#include <numeric>
#include <vector>

TEMPLATE_TEST_CASE("statistics.mean simple", "", float, double)
{
    auto const vec = std::vector<TestType>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    auto const mean_stl = st::cpp::mean_stl(std::begin(vec), std::end(vec));
    auto const mean_cpp = st::cpp::mean(std::begin(vec), std::end(vec));
    auto const mean = st::mean(std::begin(vec), std::end(vec));

    CHECK(mean == mean_stl);
    CHECK(mean == mean_cpp);
    CHECK(mean == TestType(5.5));
}

TEMPLATE_TEST_CASE("statistics.mean", "", float, double)
{
    auto vec = std::vector<TestType>(1000);
    std::iota(std::begin(vec), std::end(vec), TestType{});

    auto const mean_stl = st::cpp::mean_stl(std::begin(vec), std::end(vec));
    auto const mean_cpp = st::cpp::mean(std::begin(vec), std::end(vec));
    auto const mean_boost = boost::math::statistics::mean(vec);
    auto const mean = st::mean(std::begin(vec), std::end(vec));

    CHECK(mean == Catch::Approx(mean_stl).margin(1e-3));
    CHECK(mean == Catch::Approx(mean_cpp).margin(1e-3));
    CHECK(mean == Catch::Approx(mean_boost).margin(1e-3));
}

TEMPLATE_TEST_CASE("statistics.mean_and_sample_variance", "", float, double)
{
    auto vec = std::vector<TestType>(1000);
    std::iota(std::begin(vec), std::end(vec), TestType{});

    auto const [mean_cpp, sample_variance_cpp] = st::cpp::mean_and_sample_variance(std::begin(vec), std::end(vec));
    auto const [mean_boost, sample_variance_boost] = boost::math::statistics::mean_and_sample_variance(vec);
    auto const [mean, sample_variance] = st::mean_and_sample_variance(std::begin(vec), std::end(vec));

    CHECK(std::abs(mean / mean_boost - TestType(1.0)) < TestType(1e-2));
    CHECK(mean == Catch::Approx(mean_cpp).margin(1e-3));
    CHECK(std::abs(sample_variance / sample_variance_boost - TestType(1.0)) < TestType(1e-2));
    CHECK(sample_variance == Catch::Approx(sample_variance_cpp).margin(1e-3));
}
