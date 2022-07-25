#ifndef SIMD_TESTBED_IMAGE_PROCESSING_THRESHOLD_HPP
#define SIMD_TESTBED_IMAGE_PROCESSING_THRESHOLD_HPP

#include <simd_testbed/image_processing/detail/threshold_impl.hpp>

#include <iterator>
#include <type_traits>

namespace st {

struct threshold_binary{};
struct threshold_binary_inverse{};
struct threshold_truncate{};
struct threshold_to_zero{};
struct threshold_to_zero_inverse{};

template <typename T>
concept threshold = detail::is_one_of
<
    T,
    threshold_binary,
    threshold_binary_inverse,
    threshold_truncate,
    threshold_to_zero,
    threshold_to_zero_inverse
>;

template <typename InIt, typename OutIt, threshold Threshold>
void apply_threshold(
    InIt first, InIt last, OutIt d_first,
    typename std::iterator_traits<InIt>::value_type threshold_value, Threshold)
{
    auto const n = std::distance(first, last);
    if constexpr (std::is_same_v<Threshold, threshold_binary>)
    {
        detail::apply_threshold_binary(&*first, n, &*d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_binary_inverse>)
    {
        detail::apply_threshold_binary_inverse(&*first, n, &*d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_truncate>)
    {
        detail::apply_threshold_truncate(&*first, n, &*d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_to_zero>)
    {
        detail::apply_threshold_to_zero(first, last, d_first, threshold_value);
    }
    else if constexpr (std::is_same_v<Threshold, threshold_to_zero_inverse>)
    {
        detail::apply_threshold_to_zero_inverse(first, last, d_first, threshold_value);
    }
}


} // namespace st

#endif
