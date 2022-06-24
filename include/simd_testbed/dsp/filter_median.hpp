#ifndef SIMD_TESTBED_DSP_FILTER_MEDIAN_HPP
#define SIMD_TESTBED_DSP_FILTER_MEDIAN_HPP

#include <algorithm>
#include <array>
#include <concepts>
#include <cstdint>
#include <iterator>

namespace st {

// Precondition: first != d_first. TODO: make in-place filter possible
template
<
    std::ptrdiff_t K,
    std::random_access_iterator InIt,
    std::sentinel_for<InIt> S,
    std::output_iterator<typename std::iterator_traits<InIt>::value_type> OutIt
>
void filter_median(InIt first, S last, OutIt d_first)
{
    static_assert(K > 0);
    using T = typename std::iterator_traits<InIt>::value_type;
    auto constexpr k_halfes = K / 2;

    auto const n = std::distance(first, last);
    auto i = std::ptrdiff_t{};
    auto window = std::array<T, static_cast<std::size_t>(K)>{};

    if (n < K)
    {
        return;
    }

    for (; i < k_halfes; ++i)
    {
        std::fill_n(std::begin(window), k_halfes - i, *first);
        std::copy_n(first, k_halfes + 1 + i, std::begin(window) + k_halfes - i);
        std::nth_element(std::begin(window), std::begin(window) + k_halfes, std::end(window));
        *d_first++ = window[k_halfes];
    }

    for (; i < n - k_halfes; ++i)
    {
        std::partial_sort_copy(
            first + i - k_halfes, first + i + k_halfes + 1,
            std::begin(window), std::begin(window) + k_halfes + 1
        );
        *d_first++ = window[k_halfes];
    }

    for (; i < n; ++i)
    {
        std::copy_n(first + i - k_halfes, n - i + 1, std::begin(window));
        std::fill(std::begin(window) + n - i + 1, std::end(window), *(last - 1));
        std::nth_element(std::begin(window), std::begin(window) + k_halfes, std::end(window));
        *d_first++ = window[k_halfes];
    }
}

} // namespace st

#endif
