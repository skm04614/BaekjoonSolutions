#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull ARR[200200];
ull MIN_SEG_TREE[800800];
ull SUM_SEG_TREE[800800];
ull LAZY[800800];
int N;

inline ull min(ull x, ull y)
{
	return x < y ? x : y;
}

void init(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		MIN_SEG_TREE[node] = SUM_SEG_TREE[node] = ARR[idx0];
		return;
	}

	int mid = (idx0 + idx1) / 2;
	init(2 * node, idx0, mid);
	init(2 * node + 1, mid + 1, idx1);

	MIN_SEG_TREE[node] = min(MIN_SEG_TREE[2 * node], MIN_SEG_TREE[2 * node + 1]);
	SUM_SEG_TREE[node] = SUM_SEG_TREE[2 * node] + SUM_SEG_TREE[2 * node + 1];
}

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		MIN_SEG_TREE[node] += LAZY[node];
		SUM_SEG_TREE[node] += static_cast<ull>(idx1 - idx0 + 1) * LAZY[node];

		if (idx0 != idx1)
		{
			LAZY[2 * node] += LAZY[node];
			LAZY[2 * node + 1] += LAZY[node];
		}

		LAZY[node] = 0;
	}
}

void increment(int node, int idx0, int idx1, int left, int right, int k)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		LAZY[node] += k;
		propagate(node, idx0, idx1);
		return;
	}
	
	int mid = (idx0 + idx1) / 2;
	increment(2 * node, idx0, mid, left, right, k);
	increment(2 * node + 1, mid + 1, idx1, left, right, k);

	MIN_SEG_TREE[node] = min(MIN_SEG_TREE[2 * node], MIN_SEG_TREE[2 * node + 1]);
	SUM_SEG_TREE[node] = SUM_SEG_TREE[2 * node] + SUM_SEG_TREE[2 * node + 1];
}

ull query_min(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return 0xFFFFFFFFFFFFFFFF;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return MIN_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return min(query_min(2 * node, idx0, mid, left, right), query_min(2 * node + 1, mid + 1, idx1, left, right));
}

ull query_sum(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SUM_SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query_sum(2 * node, idx0, mid, left, right) + query_sum(2 * node + 1, mid + 1, idx1, left, right);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int Q;
	std::cin >> N >> Q;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i];
	}

	init(1, 1, N);

	for (int i = 1; i <= Q; i++)
	{
		char q;
		int a, b;
		std::cin >> q >> a >> b;
		if (q == 'M')
		{
			std::cout << query_min(1, 1, N, a, b) << '\n';
		}
		else if (q == 'P')
		{
			int c;
			std::cin >> c;
			increment(1, 1, N, a, b, c);
		}
		else
		{
			std::cout << query_sum(1, 1, N, a, b) << '\n';
		}
	}

	return 0;
}