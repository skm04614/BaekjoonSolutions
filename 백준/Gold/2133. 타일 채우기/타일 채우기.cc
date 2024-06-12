#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


unsigned long long DP[40];

int main(void)
{
	DP[0] = 1;
    DP[2] = 3;
	for (int n = 4; n <= 30; n += 2)
	{
		DP[n] = (4 * DP[n - 2] - DP[n - 4] + 1000000007) % 1000000007;
	}

	int N;
	scanf("%d", &N);
	printf("%llu", DP[N]);

	return 0;
}