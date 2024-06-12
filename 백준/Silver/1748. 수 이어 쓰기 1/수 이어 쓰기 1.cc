#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

int main(void)
{
	int n;
	scanf("%d", &n);

	int tmp = 1;
	int digits = 0;
	int m = n;
	while (m)
	{
		tmp *= 10;
		m /= 10;
		digits++;
	}

	int sol = 0;
	while (n)
	{
		tmp /= 10;
		sol += (n - tmp + 1) * digits;
		n = tmp - 1;
		digits--;
	}
	printf("%d", sol);

	return 0;
}
