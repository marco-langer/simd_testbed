#include <simd_testbed/image_processing/threshold_cpp.hpp>
#include <simd_testbed/image_processing/threshold.hpp>
#include <simd_testbed/integer_literals.hpp>

#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_template_test_macros.hpp>

#include <cstdint>
#include <limits>
#include <vector>

using namespace st::literals::integer_literals;

TEMPLATE_TEST_CASE("image_processing.threshold binary", "", std::uint8_t)
{
    auto const input_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155
    };
    auto const threshold = TestType(127);
    auto const min = std::numeric_limits<TestType>::min();
    auto const max = std::numeric_limits<TestType>::max();
    auto const expected_data = std::vector<TestType>
    {
        min, min, min, min,
        max, min, max, min,
        min, max, min, min,
        min, min, min, max,
        min, min, max, max,
        min, min, min, min,
        max, min, max, min,
        min, max, min, min,
        min, min, min, max,
        min, min, max, max
    };

    auto data_cpp = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::cpp::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data_cpp),
        threshold, st::cpp::threshold_binary{}));

    REQUIRE(data_cpp == expected_data);

    auto data = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data),
        threshold, st::threshold_binary{}));

    REQUIRE(data == expected_data);
}

TEMPLATE_TEST_CASE("image_processing.threshold binary inverse", "", std::uint8_t)
{
    auto const input_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
    };
    auto const threshold = TestType(127);
    auto const min = std::numeric_limits<TestType>::min();
    auto const max = std::numeric_limits<TestType>::max();
    auto const expected_data = std::vector<TestType>
    {
        max, max, max, max,
        min, max, min, max,
        max, min, max, max,
        max, max, max, min,
        max, max, min, min,
        max, max, max, max,
        min, max, min, max,
        max, min, max, max,
        max, max, max, min,
        max, max, min, min
    };

    auto data_cpp = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::cpp::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data_cpp),
        threshold, st::cpp::threshold_binary_inverse{}));

    REQUIRE(data_cpp == expected_data);

    auto data = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data),
        threshold, st::threshold_binary_inverse{}));

    REQUIRE(data == expected_data);
}

TEMPLATE_TEST_CASE("image_processing.threshold truncate", "", std::uint8_t)
{
    auto const input_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
    };
    auto const threshold = TestType(127);
    auto const expected_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        threshold, 55, threshold, 0,
        78, threshold, 99, 1,
        threshold, threshold, 12, threshold,
        44, 55, threshold, threshold,
        123, 65, 11, 0,
        threshold, 55, threshold, 0,
        78, threshold, 99, 1,
        threshold, threshold, 12, threshold,
        44, 55, threshold, threshold
    };

    auto data_cpp = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::cpp::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data_cpp),
        threshold, st::cpp::threshold_truncate{}));

    REQUIRE(data_cpp == expected_data);

    auto data = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data),
        threshold, st::threshold_truncate{}));

    REQUIRE(data == expected_data);
}

TEMPLATE_TEST_CASE("image_processing.threshold to zero", "", std::uint8_t)
{
    auto const input_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155
    };
    auto const threshold = TestType(127);
    auto const min = std::numeric_limits<TestType>::min();
    auto const expected_data = std::vector<TestType>
    {
        min, min, min, min,
        222, min, 255, min,
        min, 128, min, min,
        min, min, min, 254,
        min, min, 144, 155,
        min, min, min, min,
        222, min, 255, min,
        min, 128, min, min,
        min, min, min, 254,
        min, min, 144, 155
    };

    auto data_cpp = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::cpp::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data_cpp),
        threshold, st::cpp::threshold_to_zero{}));

    REQUIRE(data_cpp == expected_data);

    auto data = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data),
        threshold, st::threshold_to_zero{}));

    REQUIRE(data == expected_data);
}

TEMPLATE_TEST_CASE("image_processing.threshold to zero inverse", "", std::uint8_t)
{
    auto const input_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155,
        123, 65, 11, 0,
        222, 55, 255, 0,
        78, 128, 99, 1,
        127, 127, 12, 254,
        44, 55, 144, 155
    };
    auto const threshold = TestType(127);
    auto const min = std::numeric_limits<TestType>::min();
    auto const expected_data = std::vector<TestType>
    {
        123, 65, 11, 0,
        min, 55, min, 0,
        78, min, 99, 1,
        127, 127, 12, min,
        44, 55, min, min,
        123, 65, 11, 0,
        min, 55, min, 0,
        78, min, 99, 1,
        127, 127, 12, min,
        44, 55, min, min
    };

    auto data_cpp = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::cpp::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data_cpp),
        threshold, st::cpp::threshold_to_zero_inverse{}));

    REQUIRE(data_cpp == expected_data);

    auto data = std::vector<TestType>(input_data.size());
    REQUIRE_NOTHROW(st::apply_threshold(
        std::cbegin(input_data), std::cend(input_data), std::begin(data),
        threshold, st::threshold_to_zero_inverse{}));

    REQUIRE(data == expected_data);
}
