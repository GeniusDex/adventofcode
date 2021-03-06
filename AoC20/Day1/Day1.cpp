#include <array>
#include <iostream>
#include <iterator>

// https://stackoverflow.com/a/26351623
template <typename... T>
constexpr auto make_array(T&&... values) ->
std::array<
    typename std::decay<
    typename std::common_type<T...>::type>::type,
    sizeof...(T)> {
    return std::array<
        typename std::decay<
        typename std::common_type<T...>::type>::type,
        sizeof...(T)>{std::forward<T>(values)...};
}

template<typename T>
constexpr void swap(T& a, T& b)
{
    const auto c = a;
    a = b;
    b = c;
}

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
    first = ::find_if_not(first, last, p);
    if (first == last) return first;

    for (ForwardIt i = std::next(first); i != last; ++i) {
        if (p(*i)) {
            ::swap(*i, *first);
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
    ForwardIt middle1 = ::partition(first, last,
        [pivot](const auto& em) { return em < pivot; });
    ForwardIt middle2 = ::partition(middle1, last,
        [pivot](const auto& em) { return !(pivot < em); });
    quicksort(first, middle1);
    quicksort(middle2, last);
}

template<size_t N>
constexpr std::array<int, N> sorted(const std::array<int, N>& in)
{
    std::array<int, N> out(in);
    quicksort(out.begin(), out.end());
    return out;
}

template<size_t N>
constexpr int findPairThatSumsTo(const std::array<int, N>& arr, int sum)
{
    size_t a = 0;
    size_t b = N - 1;
    while ((a != b) && (arr[a] + arr[b] != sum))
    {
        if (arr[a] + arr[b] > sum)
            --b;
        else
            ++a;
    }
    if (a == b)
        return 0;
    else
        return arr[a] * arr[b];
}

template<size_t N>
constexpr int calculateA(const std::array<int, N>& input)
{
    return findPairThatSumsTo(sorted(input), 2020);
}

template<size_t N>
constexpr int calculateB(const std::array<int, N>& input)
{
    const auto arr = sorted(input);
    for (size_t a = 0; a < N-2; a++)
    {
        int result = findPairThatSumsTo(arr, 2020 - arr[a]);
        if (result > 0)
            return result * arr[a];
    }
    return 0;
}

int main()
{
    //constexpr auto input = make_array(1721, 979, 366, 299, 675, 1456);
    constexpr auto input = make_array(1438,781,1917,1371,1336,1802,1566,1878,737,1998,1488,1372,1715,1585,1676,1810,1692,1329,1916,1854,1307,1347,1445,1475,1435,1270,1949,1957,1602,1931,1505,1636,1539,1803,1011,1821,1021,1461,1755,1332,1576,1923,1899,1574,1641,1357,1509,1877,1875,1228,1725,1808,1678,1789,1719,1691,1434,1538,2002,1569,1403,1146,1623,1328,1876,520,1930,1633,1990,1330,1402,1880,1984,1938,1898,1908,1661,1335,1424,1833,1731,1568,1659,1554,1323,1344,1999,1716,1851,1313,1531,190,1834,1592,1890,1649,1430,1599,869,1460,1009,1771,1818,1853,1544,1279,1997,1896,1272,1772,1375,1373,1689,1249,1840,1528,1749,1364,1670,1361,1408,1828,1864,1826,1499,1507,336,1532,1349,1519,1437,1720,1817,1920,1388,1288,1290,1823,1690,1331,1564,1660,1598,1479,1673,1553,1991,66,1571,1453,1398,1814,1679,1652,1687,1951,1334,1319,1605,1757,1517,1724,2008,1601,1909,1286,1780,1901,1961,1798,1628,1831,1277,1297,1744,1946,1407,1856,1922,1476,1836,1240,1591,1572,2000,1813,1695,1723,1238,1588,1881,1850,1298,1411,1496,744,1477,1459,1333,1902);

    constexpr int a = calculateA(input);
    constexpr int b = calculateB(input);
    std::cout << a << std::endl;
    std::cout << b << std::endl;

    return 0;
}

