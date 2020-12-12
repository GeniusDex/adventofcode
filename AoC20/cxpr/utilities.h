#pragma once

namespace cxpr
{

template<typename T>
constexpr void swap(T& a, T& b)
{
    const auto c = a;
    a = b;
    b = c;
}

} // namespace cxpr