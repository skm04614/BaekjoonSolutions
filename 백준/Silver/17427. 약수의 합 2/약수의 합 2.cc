#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull F[1001000];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int n = 1; n <= 1000000; ++n)
    {
        for (int j = 1; j * n <= 1000000; ++j)
        {
            F[j * n] += n;
        }
    }

    int n;
    std::cin >> n;
    ull g = 0;
    for (int i = 1; i <= n; ++i)
    {
        g += F[i];
    }
    std::cout << g;

    return 0;
}
