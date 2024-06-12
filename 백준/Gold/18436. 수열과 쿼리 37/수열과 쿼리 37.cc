#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[100010];
int N;
int M;
int ODD_SEG_TREE[400040];

void init(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		ODD_SEG_TREE[node] = (ARR[idx0] % 2);
		return;
	}

	int mid = (idx0 + idx1) / 2;
	init(2 * node, idx0, mid);
	init(2 * node + 1, mid + 1, idx1);

	ODD_SEG_TREE[node] = ODD_SEG_TREE[2 * node] + ODD_SEG_TREE[2 * node + 1];
}

void apply_change(int node, int idx0, int idx1, int target_idx, int v)
{
	if (target_idx < idx0 || target_idx > idx1)
	{
		return;
	}

	if (idx0 == idx1)
	{
		ODD_SEG_TREE[node] = (v % 2);
		return;
	}

	int mid = (idx0 + idx1) / 2;
	apply_change(2 * node, idx0, mid, target_idx, v);
	apply_change(2 * node + 1, mid + 1, idx1, target_idx, v);

	ODD_SEG_TREE[node] = ODD_SEG_TREE[2 * node] + ODD_SEG_TREE[2 * node + 1];
}

int query_odd(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return ODD_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query_odd(2 * node, idx0, mid, left, right) + query_odd(2 * node + 1, mid + 1, idx1, left, right);
}

int query_even(int node, int idx0, int idx1, int left, int right)
{
	int cnt = right - left + 1;

	return cnt - query_odd(node, idx0, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i];
	}
	init(1, 1, N);

	std::cin >> M;
	for (int i = 1; i <= M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			apply_change(1, 1, N, b, c);
		}
		else if (a == 2)
		{
			std::cout << query_even(1, 1, N, b, c) << '\n';
		}
		else
		{
			std::cout << query_odd(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}