#include <cstdio>

int gRecord[1000001] = { 0, 1, 2 };

int sol(int n)
{
	if (gRecord[n]) return gRecord[n];

	return gRecord[n] = (sol(n - 1) + sol(n - 2)) % 15746;
}

int main(void)
{
	int N;
	scanf("%d", &N);

	printf("%d", sol(N));

	return 0;
}