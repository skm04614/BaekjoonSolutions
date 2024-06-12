#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
char POOL[100010];
int CNT[10];

int factorial(int n)
{
	static int _factorial[20] = { 1, 1 };
	if (_factorial[n] == 0)
	{
		_factorial[n] = n * factorial(n - 1);
	}

	return _factorial[n];
}

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
	int sol = factorial(n) / factorial(m) / factorial(n - m);
	printf("%d", sol);

	return 0;
}