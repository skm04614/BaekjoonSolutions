#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int l, p, v;

    for (int t = 1; ; ++t)
    {
        std::cin >> l >> p >> v;
        if (l == 0 && p == 0 && v == 0)
        {
            break;
        }

        std::cout << "Case " << t << ": " << (l * (v / p) + min(v % p, l)) << '\n';
    }

    return 0;
}