#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

int REC[10000];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (ull n = 1; n <= 10000; ++n)
    {
        if (n % 2 == 0 || n % 5 == 0)
        {
            continue;
        }

        int cnt = 1;
        ull x = 1;
        while (x < n)
        {
            x = 10 * x + 1;
            ++cnt;
        }

        while (x = (x % n))
        {
            x = 10 * x + 1;
            ++cnt;
        }

        REC[n] = cnt;
    }

    int n;
    while (std::cin >> n)
    {
        std::cout << REC[n] << '\n';
    }

    return 0;
}
