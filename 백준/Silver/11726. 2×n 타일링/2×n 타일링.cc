#include <cstdio>

int gRecord[1001] = { 0, 1, 2 };

int sol(int n)
{
	if (gRecord[n]) return gRecord[n];

	return gRecord[n] = (sol(n - 1) + sol(n - 2)) % 10007;
}

int main(void)
{
	int n;
	scanf("%d", &n);
	printf("%d", sol(n));
	return 0;
}