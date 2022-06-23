#ifndef SIMD_TESTBED_UTILITIES_RANDOM_HPP
#define SIMD_TESTBED_UTILITIES_RANDOM_HPP

#include <simd_testbed/traits.hpp>

#include <concepts>
#include <cstdint>
#include <limits>
#include <random>
#include <type_traits>

namespace st::utilities {

template <std::integral I>
class random_generator
{
    using promoted_type = std::conditional_t
    <
        (sizeof(I) > 1),
        I,
        std::conditional_t
        <
            std::is_signed_v<I>, std::int16_t, std::uint16_t
        >
    >;

public:
    random_generator(
        I min = std::numeric_limits<I>::min(),
        I max = std::numeric_limits<I>::max(),
        unsigned int seed = std::random_device{}())
      : engine(seed)
      , dist(min, max) {}

    [[nodiscard]] auto operator()() -> I
    {
        return static_cast<I>(dist(engine));
    }

private:
    std::mt19937 engine;
    std::uniform_int_distribution<promoted_type> dist;
};

template <std::floating_point F>
class random_real_generator
{
public:
    random_real_generator(
        F min = std::numeric_limits<F>::min(),
        F max = std::numeric_limits<F>::max(),
        unsigned int seed = std::random_device{}())
      : engine(seed)
      , dist(min, max)
    {}

    [[nodiscard]] auto operator()() -> F
    {
        return dist(engine);
    }

private:
    std::mt19937 engine;
    std::uniform_real_distribution<F> dist;
};

} // namespace st::utilities

#endif
