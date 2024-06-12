#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 1000000007;

int DP[5010][5010];


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N = 5000;
    DP[0][0] = 1;
    for (int n = 1; n <= N; ++n)
    {
        DP[n][0] = DP[n - 1][1];

        for (int i = 1; i <= n; ++i)
        {
            DP[n][i] = (DP[n - 1][i + 1] + DP[n - 1][i - 1]) % MOD;
        }
    }

    int T;
    std::cin >> T;
    while (T--)
    {
        int v;
        std::cin >> v;
        std::cout << DP[v][0] << '\n';
    }

    return 0;
}
