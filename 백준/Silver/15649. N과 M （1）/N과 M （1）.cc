#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int N, M;

void sol(int* arr, bool* visited, int cnt = 0)
{
	if (cnt == M)
	{
		for (int i = 0; i < M; i++)
		{
			printf("%d ", arr[i]);
		}
		printf("\n");
		return;
	}

	for (int n = 1; n <= N; n++)
	{
		if (visited[n])
		{
			continue;
		}

		arr[cnt] = n;
		visited[n] = true;
		sol(arr, visited, cnt + 1);
		visited[n] = false;
	}
}

int main(void)
{
	scanf("%u %u", &N, &M);
	int* arr = new int[M] {};
	bool* visited = new bool[N + 1] {};
	sol(arr, visited);
	delete[] arr;
	delete[] visited;

	return 0;
}