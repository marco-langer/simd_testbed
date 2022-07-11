#ifndef SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_CPP_HPP
#define SIMD_TESTBED_LINEAR_ALGEBRA_MATRIX_CPP_HPP

#include <simd_testbed/linear_algebra/detail/matrix_cpp_impl.hpp>
#include <simd_testbed/linear_algebra/matrix_traits.hpp>

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <initializer_list>
#include <type_traits>

namespace st::cpp {

template <typename T, std::size_t Rows, std::size_t Cols>
class basic_matrix
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = T const&;
    using pointer = T*;
    using const_pointer = T const*;
    using iterator = T*;
    using const_iterator = T const*;
    constexpr static std::size_t rows = Rows;
    constexpr static std::size_t cols = Cols;

    basic_matrix() = default;
    explicit constexpr basic_matrix(std::initializer_list<T> il) noexcept
    {
        assert(std::size(il) == rows * cols);
        std::copy(std::cbegin(il), std::cend(il), std::begin(data_));
    }

    [[nodiscard]] constexpr auto
    operator()(std::size_t i, std::size_t j) noexcept -> reference
    {
        return data_[i * cols + j];
    }

    [[nodiscard]] constexpr auto
    operator()(std::size_t i, std::size_t j) const noexcept -> const_reference
    {
        return data_[i * cols + j];
    }

    [[nodiscard]] friend constexpr auto
    operator==(basic_matrix const& lhs, basic_matrix const& rhs) noexcept
        -> bool
    {
        return std::equal(
            std::cbegin(lhs.data_), std::cend(lhs.data_),
            std::cbegin(rhs.data_)
        );
    }

    [[nodiscard]] friend constexpr auto
    operator!=(basic_matrix const& lhs, basic_matrix const& rhs) noexcept
        -> bool
    {
        return !(lhs == rhs);
    }

    [[nodiscard]] constexpr auto
    begin() noexcept -> iterator
    {
        return std::begin(data_);
    }

    [[nodiscard]] constexpr auto
    end() noexcept -> iterator
    {
        return std::end(data_);
    }

    [[nodiscard]] constexpr auto
    begin() const noexcept -> const_iterator
    {
        return std::begin(data_);
    }

    [[nodiscard]] constexpr auto
    end() const noexcept -> const_iterator
    {
        return std::end(data_);
    }

    [[nodiscard]] constexpr auto
    cbegin() const noexcept -> const_iterator
    {
        return std::cbegin(data_);
    }

    [[nodiscard]] constexpr auto
    cend() const noexcept -> const_iterator
    {
        return std::cend(data_);
    }

private:
    T data_[rows * cols];
};

} // namespace st::cpp

namespace st {

template <typename T, std::size_t Rows, std::size_t Cols>
struct is_matrix<cpp::basic_matrix<T, Rows, Cols>> : std::true_type {};

namespace cpp {

template
<
    typename T,
    std::size_t RowsLhs, std::size_t ColsLhs,
    std::size_t RowsRhs, std::size_t ColsRhs
>
[[nodiscard]] constexpr auto
operator*(
        basic_matrix<T, RowsLhs, ColsLhs> const& lhs,
        basic_matrix<T, RowsRhs, ColsRhs> const& rhs) noexcept
    -> basic_matrix<T, RowsLhs, ColsRhs>
    requires (ColsLhs == RowsRhs)
{
    return detail::matrix_mul(lhs, rhs);
}

} // namespace cpp
} // namespace st

#endif
