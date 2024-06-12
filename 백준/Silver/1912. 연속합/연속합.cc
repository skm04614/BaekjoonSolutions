#include <cstdio>

int gRecord[100001];

int max(const int& n, const int& m)
{
	return n > m ? n : m;
}

int main(void)
{
	int n;
	scanf("%d", &n);
	int sol = 0x80000000;
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &gRecord[i]);
		gRecord[i] += gRecord[i - 1];
		sol = max(sol, gRecord[i]);
		if (gRecord[i] < 0)
		{
			gRecord[i] = 0;
		}
	}
	printf("%d", sol);

	return 0;
}