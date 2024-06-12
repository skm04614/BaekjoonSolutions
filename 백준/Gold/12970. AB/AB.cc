#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char buf[51] = "";

    int n, m;
    std::cin >> n >> m;
    for (int i = 0; i < n; ++i)
    {
        buf[i] = 'A';
    }

    int c = 0;
    for (int i = n - 1; i >= 0; --i)
    {
        if (m - (i - c) < 0)
        {
            continue;
        }

        m -= (i - c++);
        buf[i] = 'B';

        if (m == 0)
        {
            break;
        }
    }

    std::cout << (m == 0 ? buf : "-1");

    return 0;
}
