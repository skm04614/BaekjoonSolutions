#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int MANA[110];
int DMG[110];

int DP[110][110];
int N;

int TARGET;
int K;

void init()
{
    for (int i = 0; i <= N; ++i)
    {
        for (int j = 0; j <= 100; ++j)
        {
            DP[i][j] = INF;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> TARGET >> K;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> MANA[i] >> DMG[i];
    }

    init();
    DP[0][0] = 0;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 0; j <= 100; ++j)
        {
            if (DP[i - 1][j] == INF)
            {
                continue;
            }

            DP[i][j] = min(DP[i][j], DP[i - 1][j]);
            int multiplier = 0;
            for (int m = 1; j + m * DMG[i] <= 100; ++m)
            {
                const int _j = j + m * DMG[i];
                multiplier += m - 1;
                DP[i][_j] = min(DP[i][_j], DP[i - 1][j] + m * MANA[i] + multiplier * K);
            }
        }
    }
    std::cout << DP[N][TARGET];

    return 0;
}
