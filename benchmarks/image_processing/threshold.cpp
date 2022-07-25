#include "../../utilities/random.hpp"
#include "../../utilities/utilities.hpp"

#include <simd_testbed/image_processing/threshold_cpp.hpp>
#include <simd_testbed/image_processing/threshold.hpp>
#include <simd_testbed/integer_literals.hpp>

#include <benchmark/benchmark.h>
#include <boost/gil/image_processing/threshold.hpp>
#include <boost/gil/algorithm.hpp>
#include <boost/gil/image.hpp>
#include <opencv2/imgproc.hpp>

#include <cstdint>
#include <limits>
#include <vector>

namespace gil = boost::gil;
using namespace st::literals::integer_literals;

namespace {

[[nodiscard]] auto create_opencv_image(std::size_t height, std::size_t width)
    -> cv::Mat
{
    auto mat = cv::Mat(static_cast<int>(height), static_cast<int>(width), CV_8UC1);
    auto random = st::utilities::random_generator<std::uint8_t>{};

    for (auto& p : cv::Mat_<std::uint8_t>{mat})
    {
        p = random();
    }

    return mat;
}

[[nodiscard]] auto create_gil_image(std::size_t height, std::size_t width)
    -> gil::gray8_image_t
{
    auto image = gil::gray8_image_t{
        static_cast<std::ptrdiff_t>(width),
        static_cast<std::ptrdiff_t>(height)};

    auto random = st::utilities::random_generator<std::uint8_t>{};
    auto random_op = [&random](auto& pixel)
    {
        pixel = random();
    };
    gil::for_each_pixel(gil::view(image), random_op);

    return image;
}

}

template <typename T>
static void threshold_binary_cpp(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::cpp::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::cpp::threshold_binary{});
    }
}

template <typename T>
static void threshold_binary_inverse_cpp(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::cpp::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::cpp::threshold_binary_inverse{});
    }
}

template <typename T>
static void threshold_truncate_cpp(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::cpp::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::cpp::threshold_truncate{});
    }
}

template <typename T>
static void threshold_to_zero_cpp(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::cpp::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::cpp::threshold_to_zero{});
    }
}

template <typename T>
static void threshold_to_zero_inverse_cpp(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::cpp::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::cpp::threshold_to_zero_inverse{});
    }
}

template <typename T>
static void threshold_binary(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::threshold_binary{});
    }
}

template <typename T>
static void threshold_binary_inverse(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::threshold_binary_inverse{});
    }
}

template <typename T>
static void threshold_truncate(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::threshold_truncate{});
    }
}

template <typename T>
static void threshold_to_zero(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::threshold_to_zero{});
    }
}

template <typename T>
static void threshold_to_zero_inverse(benchmark::State& state)
{
    auto const input_data = st::utilities::generate_random_data<T>();
    auto const threshold_value = T{std::numeric_limits<T>::max() / 2};
    auto data = std::vector<T>(input_data.size());

    for (auto _ : state)
    {
        st::apply_threshold(
            std::cbegin(input_data), std::cend(input_data), std::begin(data),
            threshold_value, st::threshold_to_zero_inverse{});
    }
}

static void threshold_binary_opencv(benchmark::State& state)
{
    auto const input_data = create_opencv_image(1024, 1024);
    auto data = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(input_data, data, 127_u8, 255_u8, cv::THRESH_BINARY);
    }
}

static void threshold_binary_inverse_opencv(benchmark::State& state)
{
    auto const input_data = create_opencv_image(1024, 1024);
    auto data = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(input_data, data, 127_u8, 255_u8, cv::THRESH_BINARY_INV);
    }
}

static void threshold_binary_truncate_opencv(benchmark::State& state)
{
    auto const input_data = create_opencv_image(1024, 1024);
    auto data = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(input_data, data, 127_u8, 255_u8, cv::THRESH_TRUNC);
    }
}

static void threshold_binary_to_zero_opencv(benchmark::State& state)
{
    auto const input_data = create_opencv_image(1024, 1024);
    auto data = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(input_data, data, 127_u8, 255_u8, cv::THRESH_TOZERO);
    }
}

static void threshold_binary_to_zero_inverse_opencv(benchmark::State& state)
{
    auto const input_data = create_opencv_image(1024, 1024);
    auto data = cv::Mat{};

    for (auto _ : state)
    {
        cv::threshold(input_data, data, 127_u8, 255_u8, cv::THRESH_TOZERO_INV);
    }
}

static void threshold_binary_boost(benchmark::State& state)
{
    auto const input_data = create_gil_image(1024, 1024);
    auto data = gil::gray8_image_t{input_data.dimensions()};

    for (auto _ : state)
    {
        gil::threshold_binary(gil::const_view(input_data), gil::view(data), 127_u8);
    }
}

static void threshold_binary_inverse_boost(benchmark::State& state)
{
    auto const input_data = create_gil_image(1024, 1024);
    auto data = gil::gray8_image_t{input_data.dimensions()};

    for (auto _ : state)
    {
        gil::threshold_binary(
            gil::const_view(input_data), gil::view(data),
            127_u8, gil::threshold_direction::inverse);
    }
}

static void threshold_truncate_boost(benchmark::State& state)
{
    auto const input_data = create_gil_image(1024, 1024);
    auto data = gil::gray8_image_t{input_data.dimensions()};

    for (auto _ : state)
    {
        gil::threshold_truncate(
            gil::const_view(input_data), gil::view(data), 127_u8);
    }
}

BENCHMARK_TEMPLATE(threshold_binary_cpp, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_binary_inverse_cpp, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_truncate_cpp, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_to_zero_cpp, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_to_zero_inverse_cpp, std::uint8_t);

BENCHMARK_TEMPLATE(threshold_binary, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_binary_inverse, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_truncate, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_to_zero, std::uint8_t);
BENCHMARK_TEMPLATE(threshold_to_zero_inverse, std::uint8_t);

BENCHMARK(threshold_binary_opencv);
BENCHMARK(threshold_binary_inverse_opencv);
BENCHMARK(threshold_binary_truncate_opencv);
BENCHMARK(threshold_binary_to_zero_opencv);
BENCHMARK(threshold_binary_to_zero_inverse_opencv);

BENCHMARK(threshold_binary_boost);
BENCHMARK(threshold_binary_inverse_boost);
BENCHMARK(threshold_truncate_boost);
