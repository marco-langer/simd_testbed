#include <simd_testbed/numeric/add.hpp>

auto add_saturated(std::int8_t* first, std::int8_t* last, std::int8_t c)
{
    st::add_saturated(first, last, c);
}

auto add_saturated_intrin(std::int8_t* first, std::int8_t* last, std::int8_t c)
{
    st::add_saturated_intrin(first, last, c);
}
