#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using uint = unsigned int;

uint ARR[100010];
uint MIN_SEG_TREE[400040];
uint MAX_SEG_TREE[400040];
int N, M;

uint max(uint x, uint y)
{
	return x > y ? x : y;
}

uint min(uint x, uint y)
{
	return x < y ? x : y;
}

void init_min(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		MIN_SEG_TREE[node] = ARR[idx0];
		return;
	}

	int mid = (idx0 + idx1) / 2;

	init_min(2 * node, idx0, mid);
	init_min(2 * node + 1, mid + 1, idx1);

	MIN_SEG_TREE[node] = min(MIN_SEG_TREE[2 * node], MIN_SEG_TREE[2 * node + 1]);
}

uint get_min(int node, int idx0, int idx1, int left, int right)
{
	if (idx1 < left || idx0 > right)
	{
		return 1000000000;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return MIN_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return min(get_min(2 * node, idx0, mid, left, right), get_min(2 * node + 1, mid + 1, idx1, left, right));
}

void init_max(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		MAX_SEG_TREE[node] = ARR[idx0];
		return;
	}

	int mid = (idx0 + idx1) / 2;

	init_max(2 * node, idx0, mid);
	init_max(2 * node + 1, mid + 1, idx1);

	MAX_SEG_TREE[node] = max(MAX_SEG_TREE[2 * node], MAX_SEG_TREE[2 * node + 1]);
}

uint get_max(int node, int idx0, int idx1, int left, int right)
{
	if (idx1 < left || idx0 > right)
	{
		return 1;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return MAX_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return max(get_max(2 * node, idx0, mid, left, right), get_max(2 * node + 1, mid + 1, idx1, left, right));
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int n = 0; n < N; n++)
	{
		std::cin >> ARR[n];
	}
	init_min(1, 0, N - 1);
	init_max(1, 0, N - 1);

	for (int m = 0; m < M; m++)
	{
		int idx0, idx1;
		std::cin >> idx0 >> idx1;
		idx0--;
		idx1--;

		std::cout << get_min(1, 0, N - 1, idx0, idx1) << ' ' << get_max(1, 0, N - 1, idx0, idx1) << '\n';
	}

	return 0;
}