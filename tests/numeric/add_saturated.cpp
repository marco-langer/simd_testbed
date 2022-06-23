#include <simd_testbed/numeric/add_saturated.hpp>

#include <catch2/catch_test_macros.hpp>

#include <cstdint>
#include <vector>

TEST_CASE("numeric.add_saturated uint8_t")
{
    auto data = std::vector<std::uint8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        222, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 222
    };
    auto const c = std::uint8_t{42};
    auto expected_data = std::vector<std::uint8_t>
    {
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        255, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
        73, 74, 75, 255
    };

    REQUIRE_NOTHROW(st::add_saturated(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated_branchless uint8_t")
{
    auto data = std::vector<std::uint8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        222, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 222
    };
    auto const c = std::uint8_t{42};
    auto expected_data = std::vector<std::uint8_t>
    {
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        255, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
        73, 74, 75, 255
    };

    REQUIRE_NOTHROW(st::add_saturated_branchless(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated_intrin uint8_t")
{
    auto data = std::vector<std::uint8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        222, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 222
    };
    auto const c = std::uint8_t{142};
    auto expected_data = std::vector<std::uint8_t>
    {
        143, 144, 145, 146, 147, 148, 149, 150, 151, 152,
        255, 154, 155, 156, 157, 158, 159, 160, 161, 162,
        163, 164, 165, 166, 167, 168, 169, 170, 171, 172,
        173, 174, 175, 255
    };

    REQUIRE_NOTHROW(st::add_saturated_intrin(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated int8_t positive overflow")
{
    auto data = std::vector<std::int8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        100, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 100
    };
    auto const c = std::int8_t{42};
    auto expected_data = std::vector<std::int8_t>
    {
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        127, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
        73, 74, 75, 127
    };

    REQUIRE_NOTHROW(st::add_saturated(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated int8_t negative overflow")
{
    auto data = std::vector<std::int8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        -100, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, -100
    };
    auto const c = std::int8_t{-100};
    auto expected_data = std::vector<std::int8_t>
    {
        -99, -98, -97, -96, -95, -94, -93, -92, -91, -90,
        -128, -88, -87, -86, -85, -84, -83, -82, -81, -80,
        -79, -78, -77, -76, -75, -74, -73, -72, -71, -70,
        -69, -68, -67, -128
    };

    REQUIRE_NOTHROW(st::add_saturated(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated_intrin int8_t positive overflow")
{
    auto data = std::vector<std::int8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 100
    };
    auto const c = std::int8_t{42};
    auto expected_data = std::vector<std::int8_t>
    {
        43, 44, 45, 46, 47, 48, 49, 50, 51, 52,
        53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        63, 64, 65, 66, 67, 68, 69, 70, 71, 72,
        73, 74, 75, 127
    };

    REQUIRE_NOTHROW(st::add_saturated_intrin(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}

TEST_CASE("numeric.add_saturated_intrin int8_t negative overflow")
{
    auto data = std::vector<std::int8_t>
    {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        -100, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, -100
    };
    auto const c = std::int8_t{-100};
    auto expected_data = std::vector<std::int8_t>
    {
        -99, -98, -97, -96, -95, -94, -93, -92, -91, -90,
        -128, -88, -87, -86, -85, -84, -83, -82, -81, -80,
        -79, -78, -77, -76, -75, -74, -73, -72, -71, -70,
        -69, -68, -67, -128
    };

    REQUIRE_NOTHROW(st::add_saturated_intrin(std::begin(data), std::end(data), c));
    REQUIRE(data == expected_data);
}
