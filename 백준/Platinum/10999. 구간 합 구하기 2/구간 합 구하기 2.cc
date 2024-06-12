#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

ll ARR[1000100];
ll SEG_TREE[4000400];
ll LAZY[4000400];
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

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		SEG_TREE[node] += LAZY[node] * (idx1 - idx0 + 1);
		if (idx0 != idx1)
		{
			LAZY[2 * node] += LAZY[node];
			LAZY[2 * node + 1] += LAZY[node];
		}
		LAZY[node] = 0;
	}
}

void update(int node, int idx0, int idx1, int left, int right, ll val)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		SEG_TREE[node] += val * (idx1 - idx0 + 1);
		if (idx0 != idx1)
		{
			LAZY[2 * node] += val;
			LAZY[2 * node + 1] += val;
		}
		return;
	}

	int mid = (idx0 + idx1) / 2;
	update(2 * node, idx0, mid, left, right, val);
	update(2 * node + 1, mid + 1, idx1, left, right, val);
	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ll query(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, left, right) + query(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M >> K;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i];
	}
	init(1, 1, N);

	for (int i = 1; i <= (M + K); i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 1)
		{
			ll d;
			std::cin >> d;
			update(1, 1, N, b, c, d);
		}
		else
		{
			std::cout << query(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}