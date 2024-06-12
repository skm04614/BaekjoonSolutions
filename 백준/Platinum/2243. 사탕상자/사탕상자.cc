#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int N = 1000010;
int SEG_TREE[4000040];


void edit(int node, int idx0, int idx1, int target_idx, int diff)
{
	if (target_idx < idx0 || target_idx > idx1)
	{
		return;
	}

	SEG_TREE[node] += diff;
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx1 + idx0) / 2;
	edit(2 * node, idx0, mid, target_idx, diff);
	edit(2 * node + 1, mid + 1, idx1, target_idx, diff);
}

int get_cnt(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx1 + idx0) / 2;
	return get_cnt(2 * node, idx0, mid, left, right) + get_cnt(2 * node + 1, mid + 1, idx1, left, right);
}

int get_idx(int left, int right, int target_rank)
{
	int idx = 0;
	for (;;)
	{
		if (left > right)
		{
			break;
		}

		int mid = (left + right) / 2;
		int cumulative_rank = get_cnt(1, 0, N - 1, 0, mid);
		if (cumulative_rank >= target_rank)
		{
			right = mid - 1;
			idx = mid;
		}
		else
		{
			left = mid + 1;
		}
	}

	return idx;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int M;
	std::cin >> M;
	for (int m = 0; m < M; m++)
	{
		int op;
		std::cin >> op;
		if (op == 1)
		{
			int target_rank;
			std::cin >> target_rank;

			int target_idx = get_idx(0, N - 1, target_rank);
			std::cout << target_idx + 1 << '\n';
			edit(1, 0, N - 1, target_idx, -1);
		}
		else
		{
			int target_idx;
			int diff;
			std::cin >> target_idx >> diff;
			target_idx--;
			edit(1, 0, N - 1, target_idx, diff);
		}

	}

	return 0;
}