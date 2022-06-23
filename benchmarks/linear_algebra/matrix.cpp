#include "../../utilities/random.hpp"

#include <simd_testbed/linear_algebra/matrix.hpp>

#include <benchmark/benchmark.h>

#include <vector>

namespace {

template <st::matrix Matrix>
void fill_random(Matrix& matrix)
{
    using T = typename Matrix::value_type;

    auto random = st::utilities::random_real_generator{T{0.0}, T{1.0}};
    for (std::size_t i = 0; i < Matrix::rows; ++i)
    {
        for (std::size_t j = 0; j < Matrix::cols; ++j)
        {
            matrix(i, j) = random();
        }
    }
}

template <st::matrix Matrix>
[[nodiscard]] auto generate_random_matrices() -> std::vector<Matrix>
{
    auto result = std::vector<Matrix>(1000);
    for (auto& mat : result)
    {
        fill_random(mat);
    }
    return result;
}

} // namespace

template <st::matrix Matrix>
static void matrix_mul(benchmark::State& state)
{
    auto ms = generate_random_matrices<Matrix>();
    auto const& last = ms.back();

    for (auto _ : state)
    {
        for (auto& mat : ms)
        {
            mat = mat * last;
        }
    }
}

BENCHMARK_TEMPLATE(matrix_mul, st::basic_matrix<float, 3, 3>);
BENCHMARK_TEMPLATE(matrix_mul, st::basic_matrix<double, 3, 3>);
BENCHMARK_TEMPLATE(matrix_mul, st::basic_matrix<float, 4, 4>);
BENCHMARK_TEMPLATE(matrix_mul, st::basic_matrix<double, 4, 4>);
