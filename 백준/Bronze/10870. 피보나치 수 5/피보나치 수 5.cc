#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


unsigned long long MEMO[10010];

int main(void)
{
	MEMO[0] = 0;
	MEMO[1] = 1;

	for (int n = 2; n <= 20; n++)
	{
		MEMO[n] = (MEMO[n - 1] + MEMO[n - 2]);
	}

	unsigned long long N;
	scanf("%llu", &N);
	printf("%d", MEMO[N]);

	return 0;
}