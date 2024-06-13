#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull MIN[101] = { 0, 0, 1, 7, 4, 2, 6, 8, 10 };


inline ull min(ull x, ull y)
{
    return x < y ? x : y;
}

ull combine(ull x, ull y)
{
    ull multiplier;
    for (multiplier = 10; multiplier <= y; multiplier *= 10);
    return multiplier * x + y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int i = 2; i <= 100; ++i)
    {

    }

    for (int i = 9; i <= 100; ++i)
    {
        MIN[i] = combine(MIN[i - 6], 0);
        for (int j = 2; j <= 7; ++j)
        {
            MIN[i] = min(MIN[i], combine(MIN[i - j], MIN[j]));
            MIN[i] = min(MIN[i], combine(MIN[j], MIN[i - j]));
        }
    }

    int T;
    std::cin >> T;
    while (T--)
    {
        int n;
        std::cin >> n;
        std::cout << MIN[n] << ' ';

        if (n & 1)
        {
            std::cout << 7;
            n -= 3;
        }
        while (n)
        {
            std::cout << 1;
            n -= 2;
        }
        std::cout << '\n';
    }

    return 0;
}
