#pragma once

#include <array>
#include <string_view>

namespace cxpr
{

template<typename T, size_t Capacity>
class vector
{
public:
    constexpr vector()
        : m_size(0)
    {}

    // Element access
    constexpr T& operator[](size_t npos)
    {
        return m_storage[npos];
    }

    constexpr T const& operator[](size_t npos) const
    {
        return m_storage[npos];
    }

    // Iterators

    // Capacity
    constexpr size_t size() const
    {
        return m_size;
    }

    constexpr size_t capacity() const
    {
        return Capacity;
    }

    // Modifiers
    constexpr void push_back(const T& value)
    {
        m_storage[m_size] = value;
        ++m_size;
    }

    constexpr void push_back(T&& value)
    {
        m_storage[m_size] = std::move(value);
        ++m_size;
    }

private:
    std::array<T, Capacity> m_storage;
    size_t m_size;
};


} // namespace cxpr
