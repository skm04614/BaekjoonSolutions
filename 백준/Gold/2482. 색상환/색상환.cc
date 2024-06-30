#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
constexpr ull MOD = 1'000'000'003;

ull DP[4][1010][1010];
int N;
int K;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> K;

	DP[3][1][1] = 1;
	DP[0][1][0] = 1;
	for (int n = 2; n <= N; ++n)
	{
		DP[0][n][0] = DP[0][n - 1][0];
		for (int k = 1; k <= K; ++k)
		{
			DP[3][n][k] = DP[2][n - 1][k - 1] % MOD;
			DP[1][n][k] = DP[0][n - 1][k - 1] % MOD;

			DP[2][n][k] = (DP[3][n - 1][k] + DP[2][n - 1][k]) % MOD;
			DP[0][n][k] = (DP[1][n - 1][k] + DP[0][n - 1][k]) % MOD;
		}
	}

	ull res = (DP[2][N][K] + DP[1][N][K] + DP[0][N][K]) % MOD;
	std::cout << res;

	return 0;
}