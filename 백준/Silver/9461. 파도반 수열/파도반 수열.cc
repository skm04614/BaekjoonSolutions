#include <cstdio>

using ull = unsigned long long;

ull arr[101] = { 0, 1, 1, 1 };

ull sol(int n)
{
	if (arr[n]) return arr[n];

	return arr[n] = sol(n - 2) + sol(n - 3);
}

int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		int tgt;
		scanf("%d", &tgt);
		printf("%llu\n", sol(tgt));
	}
}