#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int sq(int val)
{
    return val * val;
}

int sol(int x1, int y1, int r1, int x2, int y2, int r2)
{
    if (x1 == x2 && y1 == y2 && r1 == r2)
    {
        return -1;
    }

    int a = sq(r1) + sq(r2) + 2 * r1 * r2;
    int b = sq(r1) + sq(r2) - 2 * r1 * r2;
    int c = sq(x1 - x2) + sq(y1 - y2);
    if (a == c || b == c)
    {
        return 1;
    }
    else if (a < c || b > c)
    {
        return 0;
    }

    return 2;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        int x1, y1, r1, x2, y2, r2;
        std::cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
        std::cout << sol(x1, y1, r1, x2, y2, r2) << '\n';
    }


    return 0;
}
