#include <cstdio>

int gRecord[100001];

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &gRecord[i]);
		gRecord[i] += gRecord[i - 1];
	}

	int idx0, idx1;
	for (int i = 0; i < m; i++)
	{
		scanf("%d %d", &idx0, &idx1);
		printf("%d\n", gRecord[idx1] - gRecord[idx0 - 1]);
	}

	return 0;
}