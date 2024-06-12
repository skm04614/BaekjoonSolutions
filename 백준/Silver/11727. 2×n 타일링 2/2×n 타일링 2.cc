#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int DP[1010];

int main(void)
{
	int N;
	scanf("%d", &N);

	DP[1] = 1;
	DP[2] = 3;

	for (int n = 3; n <= N; n++)
	{
		DP[n] = (DP[n - 1] + 2 * DP[n - 2]) % 10007;
	}


	printf("%d", DP[N]);


	return 0;
}