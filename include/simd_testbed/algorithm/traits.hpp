#ifndef SIMD_TESTBED_ALGORITHM_TRAITS
#define SIMD_TESTBED_ALGORITHM_TRAITS

#include <type_traits>

namespace st {

namespace detail {

template <typename T, typename... Ts>
inline constexpr bool is_one_of = (... || std::is_same_v<T, Ts>);

} // namespace detail

template <typename T>
struct is_standard_arithmetic : std::integral_constant
<
    bool,
    detail::is_one_of
    <
        std::remove_reference_t<T>,
        unsigned char, signed char, unsigned short, short, unsigned int, int,
        unsigned long, long, unsigned long long, long long,
        float, double
    >
> {};

template <typename T>
using is_standard_arithmetic_t = typename is_standard_arithmetic<T>::type;

template <typename T>
inline constexpr bool is_standard_arithmetic_v = is_standard_arithmetic<T>::value;

} // namespace st

#endif
