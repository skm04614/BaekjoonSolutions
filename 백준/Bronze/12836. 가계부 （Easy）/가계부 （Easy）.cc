#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

using ll = long long;

ll SEG_TREE[4004000];

void add_data(int node, int idx0, int idx1, int target_idx, ll val)
{
	if (target_idx < idx0 || idx1 < target_idx)
	{
		return;
	}

	if (idx0 == idx1)
	{
		SEG_TREE[node] += val;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	add_data(2 * node, idx0, mid, target_idx, val);
	add_data(2 * node + 1, mid + 1, idx1, target_idx, val);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ll query_date_range(int node, int idx0, int idx1, int left, int right)
{
	if (left > idx1 || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query_date_range(2 * node, idx0, mid, left, right) + query_date_range(2 * node + 1, mid + 1, idx1, left, right);
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, M;
	std::cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			add_data(1, 1, N, b, c);
		}
		else
		{
			std::cout << query_date_range(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}