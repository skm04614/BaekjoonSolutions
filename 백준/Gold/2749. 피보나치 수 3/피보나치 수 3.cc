#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

unsigned int MEMO[1500010];

int main(void)
{
	MEMO[0] = 0;
	MEMO[1] = 1;

	for (int n = 2; n <= (sizeof(MEMO) / sizeof(MEMO[0])) - 1; n++)
	{
		MEMO[n] = (MEMO[n - 1] + MEMO[n - 2]) % 1000000;
	}

	unsigned long long N;
	scanf("%llu", &N);
	printf("%d", MEMO[N % 1500000]);

	return 0;
}