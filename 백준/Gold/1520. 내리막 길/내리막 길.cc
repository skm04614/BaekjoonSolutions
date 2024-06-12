#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[510][510];
int DP[510][510];
int N, M;

struct Coords
{
	int y;
	int x;

	Coords move(int opt) const
	{
		switch (opt)
		{
		case 0:
			return { y + 1, x };
		case 1:
			return { y - 1, x };
		case 2:
			return { y, x + 1 };
		default:
			return { y, x - 1 };
		}
	}

	bool is_out_of_bounds() const
	{
		return y < 0 || x < 0 || y >= N || x >= M;
	}

	bool operator>(const Coords& other) const
	{
		return MAP[y][x] > MAP[other.y][other.x];
	}

	bool operator<(const Coords& other) const
	{
		return MAP[y][x] < MAP[other.y][other.x];
	}
};

Coords ARR[250250];
Coords TMP[250250];
int K;

template <typename T>
void merge_sort(T* arr, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;
	merge_sort(arr, tmp, idx0, mid);
	merge_sort(arr, tmp, mid + 1, idx1);

	int left = idx0;
	int right = mid + 1;
	int idx = 0;
	for (;;)
	{
		if (left > mid || right > idx1)
		{
			break;
		}

		if (arr[left] > arr[right])
		{
			tmp[idx++] = arr[left++];
		}
		else
		{
			tmp[idx++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		tmp[idx++] = arr[left++];
	}

	while (right <= idx1)
	{
		tmp[idx++] = arr[right++];
	}

	for (int i = 0; i < idx; i++)
	{
		arr[idx0 + i] = tmp[i];
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cin >> MAP[i][j];
			ARR[K++] = { i, j };
		}
	}

	DP[0][0] = 1;
	merge_sort(ARR, TMP, 0, K - 1);

	for (int k = 0; k < K; k++)
	{
		const Coords& current = ARR[k];
		if (DP[current.y][current.x] == 0)
		{
			continue;
		}

		for (int i = 0; i < 4; i++)
		{
			const Coords adjacent = current.move(i);
			if (!adjacent.is_out_of_bounds() && adjacent < current)
			{
				DP[adjacent.y][adjacent.x] += DP[current.y][current.x];
			}
		}
	}
	std::cout << DP[N - 1][M - 1];


	return 0;
}