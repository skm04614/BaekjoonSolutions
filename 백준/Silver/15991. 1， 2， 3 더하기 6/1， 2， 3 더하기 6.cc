#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int T;
int N;
unsigned long long DP[100010];

int main(void)
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);

		DP[1] = 1;
		DP[2] = 2;
		DP[3] = 2;
		DP[4] = DP[2] + 1;
		DP[5] = DP[3] + DP[1];
		DP[6] = DP[4] + DP[2] + 1;

		for (int n = 7; n <= N; n++)
		{
			DP[n] = (DP[n - 2] + DP[n - 4] + DP[n - 6]) % 1000000009;
		}

		printf("%llu\n", DP[N]);
	}

	return 0;
}