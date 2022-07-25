#ifndef SIMD_TESTBED_UTILITIES_UTILITIES
#define SIMD_TESTBED_UTILITIES_UTILITIES

#include "random.hpp"

#include <simd_testbed/integer_literals.hpp>

#include <cstdint>
#include <vector>

namespace st::utilities {

template <std::integral I>
[[nodiscard]] auto generate_random_data(std::size_t elements = 1024 * 1024)
    -> std::vector<I>
{
    using namespace st::literals::integer_literals;

    auto result = std::vector<I>{};
    result.reserve(elements);

    random_generator<I> random{
        std::numeric_limits<I>::min() + 5,
        std::numeric_limits<I>::max() - 5
    };

    for (auto i = 0_uz; i < elements; ++i)
    {
        result.push_back(random());
    }
    result.back() = std::numeric_limits<I>::max() - 3;

    return result;
}

} // namespace st

#endif
