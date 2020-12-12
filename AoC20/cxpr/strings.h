#pragma once

#include <array>
#include <string_view>

#include "vector.h"

namespace cxpr::impl
{

template<typename Fn>
constexpr void split_by_char_and_call(const std::string_view& input, char c, Fn callback)
{
    size_t start = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] == c)
        {
            callback(input.substr(start, i - start));
            start = i + 1;
        }
    }
    callback(input.substr(start));
}

template<size_t MaxNrOfWords>
constexpr void split_words_into(cxpr::vector<std::string_view, MaxNrOfWords>& out, const std::string_view& input)
{
    split_by_char_and_call(input, ' ', [&out](const std::string_view& word) { out.push_back(word); });
}

} // namespace cxpr::impl


namespace cxpr
{

constexpr size_t count_char(const std::string_view& input, const char c)
{
    size_t count = 0;
    for (size_t i = 0; i < input.length(); i++)
    {
        if (input[i] == c)
            count++;
    }
    return count;
}

constexpr size_t count_lines(const std::string_view& input)
{
    return count_char(input, '\n') + 1;
}

template<size_t NrOfLines>
constexpr auto split_lines(const std::string_view& input)
{
    std::array<std::string_view, NrOfLines> lines = {};
    size_t index = 0;
    impl::split_by_char_and_call(input, '\n', [&lines, &index](const std::string_view& line) { lines[index++] = line; });
    //size_t start = 0;
    //for (size_t i = 0; i < input.length(); i++)
    //{
    //    if (input[i] == '\n')
    //    {
    //        lines[index] = input.substr(start, i - start);
    //        index++;
    //        start = i + 1;
    //    }
    //}
    //lines[index] = input.substr(start);
    return lines;
}


template<size_t NrOfStrings>
constexpr size_t count_max_char_per_string(const std::array<std::string_view, NrOfStrings>& input, const char c)
{
    size_t max = 0;
    for (size_t i = 0; i < input.size(); i++)
    {
        auto nr_char = count_char(input[i], c);
        if (nr_char > max)
            max = nr_char;
    }
    return max;
}

template<size_t NrOfStrings>
constexpr size_t count_max_words_per_string(const std::array<std::string_view, NrOfStrings>& input)
{
    return count_max_char_per_string(input, ' ') + 1;
}

template<size_t MaxNrOfWordsPerString, size_t NrOfStrings>
constexpr auto split_words_per_string(const std::array<std::string_view, NrOfStrings>& input)
{
    std::array<vector<std::string_view, MaxNrOfWordsPerString>, NrOfStrings> out = {};
    for (size_t i = 0; i < input.size(); i++)
    {
        impl::split_words_into(out[i], input[i]);
    }
    return out;
}


} // namespace cxpr
