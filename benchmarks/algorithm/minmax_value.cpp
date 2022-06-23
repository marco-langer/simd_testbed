#include "../../utilities/utilities.hpp"

#include <simd_testbed/algorithm/detail/minmax_value_impl.hpp>
#include <simd_testbed/algorithm/algorithm.hpp>

#include <benchmark/benchmark.h>

#include <algorithm>
#include <cstdint>
#include <iostream>
#include <ranges>

template <typename I>
static void max_value(benchmark::State& state)
{
    auto const v = st::utilities::generate_data<I>();

    for (auto _ : state)
    {
        auto const result = st::max_value(std::cbegin(v), std::cend(v));
        benchmark::DoNotOptimize(result);
    }
}

template <typename I>
static void max_value_cpp(benchmark::State& state)
{
    auto const v = st::utilities::generate_data<I>();

    for (auto _ : state)
    {
        auto const result = st::detail::max_value(std::cbegin(v), std::cend(v));
        benchmark::DoNotOptimize(result);
    }
}

template <typename I>
static void std_max_element(benchmark::State& state)
{
    auto const v = st::utilities::generate_data<I>();

    for (auto _ : state)
    {
        auto const result = *std::max_element(std::cbegin(v), std::cend(v));
        benchmark::DoNotOptimize(result);
    }
}

template <typename I>
static void std_ranges_max_element(benchmark::State& state)
{
    auto const v = st::utilities::generate_data<I>();

    for (auto _ : state)
    {
        auto const result = *std::ranges::max_element(v);
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK_TEMPLATE(max_value, std::int8_t);
BENCHMARK_TEMPLATE(max_value, std::int16_t);
BENCHMARK_TEMPLATE(max_value, std::int32_t);
BENCHMARK_TEMPLATE(max_value, std::int64_t);

BENCHMARK_TEMPLATE(max_value_cpp, std::int8_t);
BENCHMARK_TEMPLATE(max_value_cpp, std::int16_t);
BENCHMARK_TEMPLATE(max_value_cpp, std::int32_t);
BENCHMARK_TEMPLATE(max_value_cpp, std::int64_t);

BENCHMARK_TEMPLATE(std_max_element, std::int8_t);
BENCHMARK_TEMPLATE(std_max_element, std::int16_t);
BENCHMARK_TEMPLATE(std_max_element, std::int32_t);
BENCHMARK_TEMPLATE(std_max_element, std::int64_t);

BENCHMARK_TEMPLATE(std_ranges_max_element, std::int8_t);
BENCHMARK_TEMPLATE(std_ranges_max_element, std::int16_t);
BENCHMARK_TEMPLATE(std_ranges_max_element, std::int32_t);
BENCHMARK_TEMPLATE(std_ranges_max_element, std::int64_t);
