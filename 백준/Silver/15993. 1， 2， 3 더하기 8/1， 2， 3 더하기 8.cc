#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int T;
int N;
unsigned long long DP[2][100010];

int main(void)
{
	DP[1][1] = 1;
	DP[0][1] = 0;
	DP[1][2] = 1;
	DP[0][2] = 1;
	DP[1][3] = 2;
	DP[0][3] = 2;

	for (int n = 4; n <= 100000; n++)
	{
		DP[1][n] = (DP[0][n - 1] + DP[0][n - 2] + DP[0][n - 3]) % 1000000009;
		DP[0][n] = (DP[1][n - 1] + DP[1][n - 2] + DP[1][n - 3]) % 1000000009;
	}

	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		printf("%llu %llu\n", DP[1][N], DP[0][N]);
	}

	return 0;
}