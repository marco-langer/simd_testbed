#include "../../utilities/random.hpp"

#include <simd_testbed/statistics/univariate_statistics_cpp.hpp>
#include <simd_testbed/statistics/univariate_statistics.hpp>

#include <benchmark/benchmark.h>
#include <boost/math/statistics/univariate_statistics.hpp>

#include <concepts>
#include <vector>

namespace {

template <std::floating_point F>
[[nodiscard]] auto generate_random_data() -> std::vector<F>
{
    constexpr auto elements = 1024 * 1024;
    auto result = std::vector<F>{};
    result.reserve(elements);

    auto random = st::utilities::random_real_generator<F>{F{0.0}, F{1.0}};

    for (auto i = 0; i < elements; ++i)
    {
        result.push_back(random());
    }
    return result;
}

} // namespace

template <std::floating_point F>
static void mean_stl(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const mean = st::cpp::mean_stl(std::begin(data), std::end(data));
        benchmark::DoNotOptimize(mean);
    }
}

template <std::floating_point F>
static void mean_cpp(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const mean = st::cpp::mean(std::begin(data), std::end(data));
        benchmark::DoNotOptimize(mean);
    }
}

template <std::floating_point F>
static void mean_boost(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const mean = boost::math::statistics::mean(data);
        benchmark::DoNotOptimize(mean);
    }
}

template <std::floating_point F>
static void mean(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const mean = st::mean(std::begin(data), std::end(data));
        benchmark::DoNotOptimize(mean);
    }
}

template <std::floating_point F>
static void mean_and_sample_variance_cpp(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const result = st::cpp::mean_and_sample_variance(std::begin(data), std::end(data));
        benchmark::DoNotOptimize(result);
    }
}

template <std::floating_point F>
static void mean_and_sample_variance_boost(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const result = boost::math::statistics::mean_and_sample_variance(data);
        benchmark::DoNotOptimize(result);
    }
}

template <std::floating_point F>
static void mean_and_sample_variance(benchmark::State& state)
{
    auto const data = generate_random_data<F>();

    for (auto _ : state)
    {
        auto const result = st::mean_and_sample_variance(std::begin(data), std::end(data));
        benchmark::DoNotOptimize(result);
    }
}

BENCHMARK_TEMPLATE(mean_stl, float);
BENCHMARK_TEMPLATE(mean_stl, double);
BENCHMARK_TEMPLATE(mean_cpp, float);
BENCHMARK_TEMPLATE(mean_cpp, double);
BENCHMARK_TEMPLATE(mean_boost, float);
BENCHMARK_TEMPLATE(mean_boost, double);
BENCHMARK_TEMPLATE(mean, float);
BENCHMARK_TEMPLATE(mean, double);

BENCHMARK_TEMPLATE(mean_and_sample_variance_cpp, float);
BENCHMARK_TEMPLATE(mean_and_sample_variance_cpp, double);
BENCHMARK_TEMPLATE(mean_and_sample_variance_boost, float);
BENCHMARK_TEMPLATE(mean_and_sample_variance_boost, double);
BENCHMARK_TEMPLATE(mean_and_sample_variance, float);
BENCHMARK_TEMPLATE(mean_and_sample_variance, double);
