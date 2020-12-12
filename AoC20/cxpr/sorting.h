#pragma once

#include <array>
#include <string_view>

#include "utilities.h"

namespace cxpr::impl
{

// https://en.cppreference.com/w/cpp/algorithm/find
template<class InputIt, class UnaryPredicate>
constexpr InputIt find_if_not(InputIt first, InputIt last, UnaryPredicate q)
{
    for (; first != last; ++first) {
        if (!q(*first)) {
            return first;
        }
    }
    return last;
}

// https://en.cppreference.com/w/cpp/algorithm/partition
template<class ForwardIt, class UnaryPredicate>
constexpr ForwardIt partition(ForwardIt first, ForwardIt last, UnaryPredicate p)
{
    first = find_if_not(first, last, p);
    if (first == last) return first;

    for (ForwardIt i = std::next(first); i != last; ++i) {
        if (p(*i)) {
            swap(*i, *first);
            ++first;
        }
    }
    return first;
}

template <class ForwardIt>
constexpr void quicksort(ForwardIt first, ForwardIt last)
{
    if (first == last) return;
    auto pivot = *std::next(first, std::distance(first, last) / 2);
    ForwardIt middle1 = partition(first, last,
        [pivot](const auto& em) { return em < pivot; });
    ForwardIt middle2 = partition(middle1, last,
        [pivot](const auto& em) { return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

} // namespace cxpr::impl

namespace cxpr
{

template<typename T, size_t N>
constexpr auto sorted(const std::array<T, N>& in)
{
    std::array<T, N> out(in);
    impl::quicksort(out.begin(), out.end());
    return out;
}

} // namespace cxpr
