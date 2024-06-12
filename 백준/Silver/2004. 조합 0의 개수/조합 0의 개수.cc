#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull min(ull x, ull y)
{
    return x < y ? x : y;
}

ull count_2(int v)
{
    ull cnt = 0;
    ull n = 1;
    while ((n <<= 1) <= v)
    {
        cnt += (v / n);
    }

    return cnt;
}

ull count_5(int v)
{
    ull cnt = 0;
    ull n = 1;
    while ((n *= 5) <= v)
    {
        cnt += (v / n);
    }

    return cnt;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;

    ull x = count_5(n) - count_5(n - m) - count_5(m);
    ull y = count_2(n) - count_2(n - m) - count_2(m);

    std::cout << (min(x, y));

    return 0;
}
