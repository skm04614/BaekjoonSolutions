#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

using ll = long long;

ll ARR[100100];
ll SEG_TREE[400400];
int N, Q;

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

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

void edit_val(int node, int idx0, int idx1, int target_idx, ll val)
{
	if (target_idx < idx0 || idx1 < target_idx)
	{
		return;
	}

	if (idx0 == idx1)
	{
		SEG_TREE[node] = val;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	edit_val(2 * node, idx0, mid, target_idx, val);
	edit_val(2 * node + 1, mid + 1, idx1, target_idx, val);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ll query_range(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query_range(2 * node, idx0, mid, left, right) + query_range(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> Q;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i];
	}
	init(1, 1, N);

	for (int i = 1; i <= Q; i++)
	{
		int x, y, a, b;
		std::cin >> x >> y >> a >> b;
		if (x > y)
		{
			int tmp = x;
			x = y;
			y = tmp;
		}
		std::cout << query_range(1, 1, N, x, y) << '\n';
		edit_val(1, 1, N, a, b);
	}

	return 0;
}