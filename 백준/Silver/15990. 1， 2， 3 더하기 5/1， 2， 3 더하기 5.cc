#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

unsigned long long DP[4][100001] = { {}, {0, 1, 0, 1}, {0, 0, 1, 1}, {0, 0, 0, 1} };

int main(void)
{
	int T;
	scanf("%d", &T);
	
	for (int i = 4; i <= 100000; i++)
	{
		DP[1][i] = (DP[2][i - 1] + DP[3][i - 1]) % 1000000009;
		DP[2][i] = (DP[3][i - 2] + DP[1][i - 2]) % 1000000009;
		DP[3][i] = (DP[1][i - 3] + DP[2][i - 3]) % 1000000009;
	}

	int n;
	for (int i = 0; i < T; i++)
	{
		scanf("%d", &n);
		printf("%llu\n", (DP[1][n] + DP[2][n] + DP[3][n]) % 1000000009);
	}

	return 0;
}
