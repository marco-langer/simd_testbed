#include "../../utilities/utilities.hpp"

#include <simd_testbed/numeric/add_saturated.hpp>

#include <benchmark/benchmark.h>

#include <cstdint>
#include <vector>

template <typename T>
static void add(benchmark::State& state)
{
    auto v = st::utilities::generate_random_data<T>();
    auto const c = T{42};

    for (auto _ : state)
    {
        st::add(std::begin(v), std::end(v), c);
    }
}

template <typename T>
static void add_saturated(benchmark::State& state)
{
    auto v = st::utilities::generate_random_data<T>();
    auto const c = T{42};

    for (auto _ : state)
    {
        st::add_saturated(std::begin(v), std::end(v), c);
    }
}

template <typename T>
static void add_saturated_branchless(benchmark::State& state)
{
    auto v = st::utilities::generate_random_data<T>();
    auto const c = T{42};

    for (auto _ : state)
    {
        st::add_saturated_branchless(std::begin(v), std::end(v), c);
    }
}

template <typename T>
static void add_saturated_intrin(benchmark::State& state)
{
    auto v = st::utilities::generate_random_data<T>();
    auto const c = T{42};

    for (auto _ : state)
    {
        st::add_saturated_intrin(std::begin(v), std::end(v), c);
    }
}

BENCHMARK_TEMPLATE(add, std::uint8_t);
BENCHMARK_TEMPLATE(add_saturated, std::uint8_t);
BENCHMARK_TEMPLATE(add_saturated_branchless, std::uint8_t);
BENCHMARK_TEMPLATE(add_saturated_intrin, std::uint8_t);

BENCHMARK_TEMPLATE(add, std::uint16_t);
BENCHMARK_TEMPLATE(add_saturated, std::uint16_t);
BENCHMARK_TEMPLATE(add_saturated_branchless, std::uint16_t);
BENCHMARK_TEMPLATE(add_saturated_intrin, std::uint16_t);

BENCHMARK_TEMPLATE(add, std::uint32_t);
BENCHMARK_TEMPLATE(add_saturated, std::uint32_t);
BENCHMARK_TEMPLATE(add_saturated_branchless, std::uint32_t);

BENCHMARK_TEMPLATE(add, std::uint64_t);
BENCHMARK_TEMPLATE(add_saturated, std::uint64_t);
BENCHMARK_TEMPLATE(add_saturated_branchless, std::uint64_t);

BENCHMARK_TEMPLATE(add, std::int8_t);
BENCHMARK_TEMPLATE(add_saturated, std::int8_t);
BENCHMARK_TEMPLATE(add_saturated_intrin, std::int8_t);

BENCHMARK_TEMPLATE(add, std::int16_t);
BENCHMARK_TEMPLATE(add_saturated, std::int16_t);
BENCHMARK_TEMPLATE(add_saturated_intrin, std::int16_t);
