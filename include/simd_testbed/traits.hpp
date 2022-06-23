#ifndef SIMD_TESTBED_TRAITS_HPP
#define SIMD_TESTBED_TRAITS_HPP

#include <concepts>
#include <iterator>
#include <type_traits>

namespace st {

namespace detail {

template <typename... T>
inline constexpr bool dependent_false = false;

template <typename T, typename... Ts>
inline constexpr bool is_one_of = (... || std::is_same_v<T, Ts>);

} // namespace detail

template <typename T>
struct is_standard_signed_integer : std::bool_constant
<
    detail::is_one_of
    <
        std::remove_cv_t<T>,
        signed char, short, int, long, long long
    >
> {};

template <typename T>
concept standard_signed_integer = is_standard_signed_integer<T>::value;

template <typename T>
struct is_standard_unsigned_integer : std::bool_constant
<
    detail::is_one_of
    <
        std::remove_cv_t<T>,
        unsigned char, unsigned short, unsigned int,
        unsigned long, unsigned long long
    >
> {};

template <typename T>
concept standard_unsigned_integer = is_standard_unsigned_integer<T>::value;

template <typename T>
inline constexpr bool is_standard_integer_v =
    std::bool_constant
    <
        is_standard_unsigned_integer<T>::value
        || is_standard_signed_integer<T>::value
    >::value;

template <typename T>
concept standard_integer = is_standard_integer_v<T>;

template <typename T>
struct is_standard_arithmetic : std::bool_constant
<
    std::is_floating_point_v<T>
    || is_standard_integer_v<T>
> {};

template <typename T>
inline constexpr bool is_standard_arithmetic_v = is_standard_arithmetic<T>::value;

template <typename T>
concept standard_arithmetic = is_standard_arithmetic_v<T>;

template <typename T>
concept integer_input_iterator =
    std::input_iterator<T> && is_standard_integer_v<typename T::value_type>;

template <typename T>
concept integer_contiguous_iterator =
    std::contiguous_iterator<T> && is_standard_integer_v<typename T::value_type>;

template <typename T>
concept arithmetic_input_iterator =
    std::input_iterator<T> && is_standard_arithmetic_v<typename T::value_type>;

template <typename T>
concept arithmetic_contiguous_iterator =
    std::contiguous_iterator<T> && is_standard_arithmetic_v<typename T::value_type>;

} // namespace st

#endif
