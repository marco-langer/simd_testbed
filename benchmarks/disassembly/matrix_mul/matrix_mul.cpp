#include <simd_testbed/linear_algebra/matrix.hpp>

using matrix4x4f = st::basic_matrix<float, 4, 4>;

auto matrix_mul(matrix4x4f const& lhs, matrix4x4f const& rhs) noexcept
{
    return lhs * rhs;
}
