#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

unsigned long long DP[1001];

int main(void)
{
	int N;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &DP[i]);
		for (int j = 1; j < i; j++)
		{
			int tmp = DP[i - j] + DP[j];
			DP[i] = DP[i] < tmp ? DP[i] : tmp;
		}
	}
	printf("%d", DP[N]);

	return 0;
}
