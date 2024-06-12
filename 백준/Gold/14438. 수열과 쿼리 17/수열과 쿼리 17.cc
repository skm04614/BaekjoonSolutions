#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int ARR[100010];
int N;
int M;
int SEG_TREE[400040];

inline int min(int x, int y)
{
	return x < y ? x : y;
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

	SEG_TREE[node] = min(SEG_TREE[2 * node], SEG_TREE[2 * node + 1]);
}

void apply_change(int node, int idx0, int idx1, int target_idx, int v)
{
	if (target_idx < idx0 || target_idx > idx1)
	{
		return;
	}

	if (idx0 == idx1)
	{
		SEG_TREE[node] = v;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	apply_change(2 * node, idx0, mid, target_idx, v);
	apply_change(2 * node + 1, mid + 1, idx1, target_idx, v);

	SEG_TREE[node] = min(SEG_TREE[2 * node], SEG_TREE[2 * node + 1]);
}

int query(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 0x7FFFFFFF;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return min(query(2 * node, idx0, mid, left, right), query(2 * node + 1, mid + 1, idx1, left, right));
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
		else
		{
			std::cout << query(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}