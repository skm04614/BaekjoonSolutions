#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int DP[1010][1010];
int Y;
int X;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> Y >> X;
    for (int i = 0; i < Y; ++i)
    {
        for (int j = 0; j < X; ++j)
        {
            char c;
            std::cin >> c;
            DP[i][j] = c == '1';
        }
    }

    int res = 0;
    for (int i = 0; i < 1000; ++i)
    {
        res = max(res, max(DP[i][0], DP[0][i]));
    }

    for (int i = 1; i < Y; ++i)
    {
        for (int j = 1; j < X; ++j)
        {
            if (DP[i][j] == 0)
            {
                continue;
            }

            DP[i][j] = min(min(DP[i - 1][j], DP[i][j - 1]), DP[i - 1][j - 1]) + 1;
            res = max(res, DP[i][j]);
        }
    }

    std::cout << res * res;

    return 0;
}
