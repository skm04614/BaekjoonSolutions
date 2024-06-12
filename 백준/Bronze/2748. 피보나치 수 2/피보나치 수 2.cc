#include <cstdio>

using ull = unsigned long long;

ull fibo[91] = { 0, 1 };

int main(void)
{
	int n;
	scanf("%d", &n);

	for (int i = 2; i <= n; i++)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}

	printf("%llu", fibo[n]);
	return 0;
}