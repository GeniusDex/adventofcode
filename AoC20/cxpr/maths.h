#pragma once

#include <array>
#include <string_view>

namespace cxpr
{

template<typename T>
constexpr auto abs(T value)
{
    if (value < 0)
        return -value;
    else
        return value;
}

} // namespace cxpr