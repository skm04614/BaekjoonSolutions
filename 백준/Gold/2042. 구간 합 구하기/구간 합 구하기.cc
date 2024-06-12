#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

ll ARR[1000010];
ll SEG_TREE[4000040];

int N, M, K;

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

ll get_sum(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 0llu;
	}

	if (idx0 >= left && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return get_sum(2 * node, idx0, mid, left, right) + get_sum(2 * node + 1, mid + 1, idx1, left, right);
}

void edit(int node, int idx0, int idx1, int target_idx, ll diff)
{
	if (idx0 > target_idx || idx1 < target_idx)
	{
		return;
	}

	SEG_TREE[node] += diff;
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;
	edit(2 * node, idx0, mid, target_idx, diff);
	edit(2 * node + 1, mid + 1, idx1, target_idx, diff);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M >> K;
	for (int n = 0; n < N; n++)
	{
		std::cin >> ARR[n];
	}
	init(1, 0, N - 1);

	for (int i = 0; i < (M + K); i++)
	{
		ll a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			b--;
			ll diff = c - ARR[b];
			ARR[b] = c;
			edit(1, 0, N - 1, b, diff);
		}
		else
		{
			b--;
			c--;
			std::cout << get_sum(1, 0, N - 1, b, c) << '\n';
		}
	}

	return 0;
}