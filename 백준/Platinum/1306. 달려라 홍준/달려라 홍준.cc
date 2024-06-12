#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1000100];
int SEG_TREE[4000400];
int N;

int max(int x, int y)
{
	return x > y ? x : y;
}

void init(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		SEG_TREE[node] = ARR[idx0];
		return;
	}

	int mid = (idx0 + idx1) / 2;
	init(2 * node, idx0, mid);
	init(2 * node + 1, mid + 1, idx1);

	SEG_TREE[node] = max(SEG_TREE[2 * node], SEG_TREE[2 * node + 1]);
}

int query(int node, int idx0, int idx1, int left, int right)
{
	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return max(query(2 * node, idx0, mid, left, right), query(2 * node + 1, mid + 1, idx1, left, right));
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int M;
	std::cin >> N >> M;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i];
	}

	init(1, 1, N);

	for (int m = M; m <= N - M + 1; m++)
	{
		std::cout << query(1, 1, N, m - (M - 1), m + (M - 1)) << ' ';
	}

	return 0;
}