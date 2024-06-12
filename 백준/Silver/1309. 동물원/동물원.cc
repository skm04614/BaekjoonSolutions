#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int DP[2][100001] = {};
constexpr int MOD = 9901;

int main(void)
{
	int N;
	scanf("%d", &N);

	DP[0][1] = 1;
	DP[1][1] = 2;

	for (int n = 2; n <= N; n++)
	{
		DP[0][n] = (DP[1][n - 1] + DP[0][n - 1]) % MOD;
		DP[1][n] = (DP[1][n - 1] + 2 * DP[0][n - 1]) % MOD;
	}

	printf("%d", (DP[0][N] + DP[1][N]) % MOD);

	return 0;
}
