#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

unsigned long long DP[201][201];

int main(void)
{
	int N, K;
	scanf("%d %d", &N, &K);

	for (int n = 0; n <= N; n++)
	{
		DP[1][n] = 1;
	}
	for (int k = 1; k <= K; k++)
	{
		DP[k][0] = 1;
	}


	for (int k = 2; k <= K; k++)
	{
		for (int n = 1; n <= N; n++)
		{
			DP[k][n] = (DP[k - 1][n] + DP[k][n - 1]) % 1000000000;
		}
	}

	printf("%d", DP[K][N]);



	return 0;
}
