#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 10007;


unsigned int DP[1010][1010];


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, K;
    std::cin >> N >> K;

    DP[0][0] = 1;
    for (int n = 1; n <= 1000; n++)
    {
        DP[n][0] = 1;
        for (int k = 1; k <= n; k++)
        {
            DP[n][k] = (DP[n - 1][k] + DP[n - 1][k - 1]) % MOD;
        }
    }
    std::cout << DP[N][K];

    return 0;
}