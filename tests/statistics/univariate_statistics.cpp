#include <simd_testbed/statistics/univariate_statistics_cpp.hpp>
#include <simd_testbed/statistics/univariate_statistics.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <cstdint>
#include <numeric>
#include <vector>

TEMPLATE_TEST_CASE("statistics.mean simple", "", float, double)
{
    auto const vec = std::vector<TestType>{1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0};

    auto const mean_stl = st::cpp::mean_stl(std::begin(vec), std::end(vec));
    REQUIRE(mean_stl == TestType(5.5));

    auto const mean_cpp = st::cpp::mean(std::begin(vec), std::end(vec));
    REQUIRE(mean_cpp == mean_stl);

    auto const mean = st::mean(std::begin(vec), std::end(vec));
    REQUIRE(mean == mean_stl);
}

TEMPLATE_TEST_CASE("statistics.mean", "", float, double)
{
    auto vec = std::vector<TestType>(1000);
    std::iota(std::begin(vec), std::end(vec), TestType{});

    auto const mean_stl = st::cpp::mean_stl(std::begin(vec), std::end(vec));
    auto const mean_cpp = st::cpp::mean(std::begin(vec), std::end(vec));
    auto const mean = st::mean(std::begin(vec), std::end(vec));

    REQUIRE(mean == mean_cpp);
    REQUIRE(mean == mean_stl);
}
