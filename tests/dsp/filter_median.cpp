#include <simd_testbed/dsp/filter_median.hpp>

#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <cstdint>
#include <vector>

TEST_CASE("dsp.filter median kernel 3")
{
    auto const data = std::vector<int>
    {
        1, 42, 53, 1, 67, 12, 99, 121, 4, 23, 89
    };
    auto constexpr kernel_size = std::size_t{3};
    auto const expected_result = std::vector<int>
    {
        1, 42, 42, 53, 12, 67, 99, 99, 23, 23, 89
    };

    auto result = std::vector<int>{};
    result.reserve(data.size());
    REQUIRE_NOTHROW(st::filter_median<kernel_size>(
        std::cbegin(data), std::cend(data), std::back_inserter(result)));

    REQUIRE(result == expected_result);
}

TEST_CASE("dsp.filter median kernel 5")
{
    auto const data = std::vector<int>
    {
        1, 42, 53, 1, 67, 12, 99, 121, 4, 23, 89
    };
    auto constexpr kernel_size = std::size_t{5};
    auto const expected_result = std::vector<int>
    {
        1, 1, 42, 42, 53, 67, 67, 23, 89, 89, 89
    };

    auto result = std::vector<int>{};
    result.reserve(data.size());
    REQUIRE_NOTHROW(st::filter_median<kernel_size>(
        std::cbegin(data), std::cend(data), std::back_inserter(result)));

    REQUIRE(result == expected_result);
}

TEST_CASE("dsp.filter median kernel 7")
{
    auto const data = std::vector<int>
    {
        1, 42, 53, 1, 67, 12, 99, 121, 4, 23, 89
    };
    auto constexpr kernel_size = std::size_t{7};
    auto const expected_result = std::vector<int>
    {
        1, 1, 12, 42, 53, 53, 23, 67, 89, 89, 89
    };

    auto result = std::vector<int>{};
    result.reserve(data.size());
    REQUIRE_NOTHROW(st::filter_median<kernel_size>(
        std::cbegin(data), std::cend(data), std::back_inserter(result)));

    REQUIRE(result == expected_result);
}
