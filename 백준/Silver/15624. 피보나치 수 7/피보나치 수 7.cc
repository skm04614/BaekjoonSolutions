#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


unsigned long long MEMO[1000010];

int main(void)
{
	MEMO[0] = 0;
	MEMO[1] = 1;

	for (int n = 2; n <= 1000000; n++)
	{
		MEMO[n] = (MEMO[n - 1] + MEMO[n - 2]) % 1000000007;
	}

	unsigned long long N;
	scanf("%llu", &N);
	printf("%llu", MEMO[N]);

	return 0;
}