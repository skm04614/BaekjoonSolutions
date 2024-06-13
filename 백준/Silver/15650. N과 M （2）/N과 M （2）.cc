#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int N, M;

void sol(int* arr, int n0 = 1, int cnt = 0)
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

	for (int n = n0; n <= N; n++)
	{
		arr[cnt] = n;
		sol(arr, n + 1, cnt + 1);
	}
}

int main(void)
{
	scanf("%u %u", &N, &M);
	int* arr = new int[M] {};
	sol(arr);
	delete[] arr;

	return 0;
}