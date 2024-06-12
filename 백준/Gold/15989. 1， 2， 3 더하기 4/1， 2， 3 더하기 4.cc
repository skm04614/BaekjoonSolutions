#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int T;
int N;
int DP[3][10010];

int main(void)
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);

		DP[1][1] = 1;
		DP[2][1] = 0;

		for (int n = 2; n <= N; n++)
		{
			DP[1][n] = DP[1][n - 1] + DP[2][n - 1] + ((n - 1) % 3 == 0);
			DP[2][n] = DP[2][n - 2] + ((n - 2) % 3 == 0);
		}

		printf("%d\n", DP[1][N] + DP[2][N] + (N % 3 == 0));
	}
}