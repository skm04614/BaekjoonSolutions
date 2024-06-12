#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 1'000'000'000;
constexpr int MAX_C = 1 << 10;

int DP[101][10][MAX_C];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    for (int i = 0; i < 10; ++i)
    {
        DP[1][i][1 << i] = 1;
    }

    for (int n = 2; n <= 100; ++n)
    {
        for (int s = 0; s < 10; ++s)
        {
            for (int k = 1; k < MAX_C; ++k)
            {
                if (s - 1 >= 0)
                {
                    DP[n][s][k | (1 << s)] = (DP[n][s][k | (1 << s)] + DP[n - 1][s - 1][k]) % MOD;
                }

                if (s + 1 <= 9)
                {
                    DP[n][s][k | (1 << s)] = (DP[n][s][k | (1 << s)] + DP[n - 1][s + 1][k]) % MOD;
                }
            }
        }
    }

    int N;
    std::cin >> N;

    int res = 0;
    for (int s = 1; s < 10; ++s)
    {
        res = (res + DP[N][s][MAX_C - 1]) % MOD;
    }
    std::cout << res;


    return 0;
}
