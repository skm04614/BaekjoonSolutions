#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int N, M;
int SOL[10];
int POOL[10] = { 1, 2, 3, 4, 5, 6, 7, 8 };
bool VISITED[10];

void _swap(int& x, int& y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void _insertion_sort(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int min_idx = i;

		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[min_idx])
			{
				min_idx = j;
			}
		}

		_swap(arr[i], arr[min_idx]);
	}
}

void sol(int depth)
{
	if (depth == M)
	{
		for (int i = 0; i < depth; i++)
		{
			std::cout << SOL[i] << ' ';
		}
		std::cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (VISITED[i])
		{
			continue;
		}

		SOL[depth] = POOL[i];
		sol(depth + 1);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		std::cin >> POOL[i];
	}
	_insertion_sort(POOL, N);

	sol(0);

	return 0;
}