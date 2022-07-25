#ifndef SIMD_TESTBED_INTEGER_LITERALS_HPP
#define SIMD_TESTBED_INTEGER_LITERALS_HPP

#include <cstdint>
#include <limits>

namespace st::literals::integer_literals {

consteval std::size_t
operator ""_uz(unsigned long long value)
{
    return static_cast<std::size_t>(value);
}

consteval std::uint8_t
operator ""_u8(unsigned long long value)
{
    if (value > std::numeric_limits<std::uint8_t>::max())
    {
        throw;
    }
    return static_cast<std::uint8_t>(value);
}

} // namespace st::literals::integer_literals

#endif
