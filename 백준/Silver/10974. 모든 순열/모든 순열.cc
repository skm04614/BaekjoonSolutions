#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

void sol(int* arr, bool* visited, int n, int m)
{
	if (n == m)
	{
		for (int i = 0; i < n; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
	}

	for (int i = 1; i <= n; i++)
	{
		if (visited[i])
		{
			continue;
		}

		visited[i] = true;
		arr[m] = i;
		sol(arr, visited, n, m + 1);
		visited[i] = false;
	}
}

int main(void)
{
	int n;
	scanf("%u", &n);
	int* arr = new int[n] {};
	bool* visited = new bool[n + 1] {};
	sol(arr, visited, n, 0);
	delete[] arr;
	delete[] visited;

	return 0;
}