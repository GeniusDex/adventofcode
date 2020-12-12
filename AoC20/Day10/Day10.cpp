#include <iostream>
#include <string_view>

#include "cxpr.h"

template<size_t N>
constexpr uint64_t calculateA(const std::array<int, N>& adapters)
{
    uint64_t ndiffs[4] = { 0 };
    ++ndiffs[adapters[0]];
    for (size_t i = 1; i < adapters.size(); ++i)
    {
        ++ndiffs[adapters[i] - adapters[i - 1]];
    }
    ++ndiffs[3];
    return ndiffs[1] * ndiffs[3];
}

template<size_t N>
constexpr uint64_t calculateB(const std::array<int, N>& adapters)
{
    const auto jolts = cxpr::concat(std::array{ 0 }, adapters, std::array{ adapters.back() + 3 });

    std::array<uint64_t, N + 2> count = { 1 };
    for (size_t i = 0; i < jolts.size(); ++i)
    {
        size_t start = (i > 3) ? i - 3 : 0;
        for (size_t j = start; j < i; ++j)
        {
            if (jolts[i] - jolts[j] <= 3)
                count[i] += count[j];
        }
    }

    return count.back();
}

int main()
{
    constexpr std::string_view input1 = R"RAW(16
10
15
5
1
11
7
19
6
12
4)RAW";

    constexpr std::string_view input2 = R"RAW(28
33
18
42
31
14
46
20
48
47
24
23
49
45
19
38
39
11
1
32
25
35
8
17
7
9
4
2
34
10
3)RAW";

    constexpr std::string_view input = R"RAW(153
17
45
57
16
147
39
121
75
70
85
134
128
115
51
139
44
65
119
168
122
72
105
31
103
89
154
114
55
25
48
38
132
157
84
71
113
143
83
64
109
129
120
100
151
79
125
22
161
167
19
26
118
142
4
158
11
35
56
18
40
7
150
99
54
152
60
27
164
78
47
82
63
46
91
32
135
3
108
10
159
127
69
110
126
133
28
15
104
138
160
98
90
144
1
2
92
41
86
66
95
12)RAW";

    constexpr auto adapters = cxpr::sorted(cxpr::parse_array<int>(cxpr::split_lines<cxpr::count_lines(input)>(input)));

    constexpr auto a = calculateA(adapters);
    constexpr auto b = calculateB(adapters);
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}
