#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

void sol(const int *pool, int size, int *arr, int sidx, int depth)
{
	if (depth == 6)
	{
		for (int i = 0; i < 6; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}

	if (depth + size - sidx < 6)
	{
			return;
	}

	for (int i = sidx; i < size; i++)
	{
		arr[depth] = pool[i];
		sol(pool, size, arr, i + 1, depth + 1);
	}
}


int main(void)
{
	int pool[14]{};
	int n = 1;

	while (n)
	{
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
		{
			scanf("%d", &pool[i]);
		}

		int arr[6]{};
		sol(pool, n, arr, 0, 0);
		printf("\n");
	}

	return 0;
}