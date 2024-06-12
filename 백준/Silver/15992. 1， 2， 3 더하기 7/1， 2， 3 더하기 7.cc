#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int T;
unsigned long long DP[1010][1010];

int main(void)
{
	DP[1][1] = 1;
	DP[2][1] = 1;
	DP[2][2] = 1;
	DP[3][1] = 1;
	DP[3][2] = 2;
	DP[3][3] = 1;

	for (int n = 4; n <= 1000; n++)
	{
		for (int m = 1; m <= n; m++)
		{
			DP[n][m] = (DP[n - 1][m - 1] + DP[n - 2][m - 1] + DP[n - 3][m - 1]) % 1000000009;
		}
	}

	scanf("%d", &T);
	while (T--)
	{
		int N, M;
		scanf("%d %d", &N, &M);
		printf("%llu\n", DP[N][M]);
	}

	return 0;
}