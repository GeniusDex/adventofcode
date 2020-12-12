#pragma once

#include <array>
#include <string_view>

namespace cxpr
{

template<typename T>
constexpr auto parse(const std::string_view& in)
{
    T out = 0;
    for (size_t i = 0; i < in.length(); i++)
    {
        out = (out * 10) + (in[i] - '0');
    }
    return out;
}

template<typename T, size_t Size>
constexpr auto parse_array(const std::array<std::string_view, Size>& in)
{
    std::array<T, Size> out = {};
    for (size_t i = 0; i < in.size(); i++)
    {
        out[i] = parse<T>(in[i]);
    }
    return out;
}

} // namespace cxpr