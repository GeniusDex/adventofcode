#pragma once

#include <array>
#include <string_view>

namespace cxpr
{

template<typename T>
constexpr auto concat()
{
    return std::array<T, 0>{};
}

template<typename T, size_t Size0, size_t... Sizes>
constexpr auto concat(const std::array<T, Size0>& head, const std::array<T, Sizes>&... ins)
{
    auto tail = concat<T, Sizes...>(ins...);
    std::array<T, (Size0 + ... + Sizes)> out = {};
    for (size_t i = 0; i < head.size(); i++)
        out[i] = head[i];
    for (size_t i = 0; i < tail.size(); i++)
        out[head.size() + i] = tail[i];
    return out;
}

} // namespace cxpr
