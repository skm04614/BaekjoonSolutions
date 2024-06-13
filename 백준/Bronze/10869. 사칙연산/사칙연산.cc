#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
	printf("%d\n%d\n%d\n%d\n%d", n + m, n - m, n * m, n / m, n % m);

	return 0;
}