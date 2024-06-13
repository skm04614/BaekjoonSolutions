#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[500500];
ull SEG_TREE[2002000];
ull LAZY[2002000];
int N, M;

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
		if ((idx1 - idx0) % 2 == 0)
		{
			SEG_TREE[node] ^= LAZY[node];
		}

		if (idx0 != idx1)
		{
			LAZY[2 * node] ^= LAZY[node];
			LAZY[2 * node + 1] ^= LAZY[node];
		}

		LAZY[node] = 0;
	}
}

void update(int node, int idx0, int idx1, int left, int right, ull val)
{
	propagate(node, idx0, idx1);

	if (idx0 > right || idx1 < left)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		if ((idx1 - idx0) % 2 == 0)
		{
			SEG_TREE[node] ^= val;
		}

		if (idx0 != idx1)
		{
			LAZY[2 * node] ^= val;
			LAZY[2 * node + 1] ^= val;
		}
		return;
	}

	int mid = (idx0 + idx1) / 2;
	update(2 * node, idx0, mid, left, right, val);
	update(2 * node + 1, mid + 1, idx1, left, right, val);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

ull query(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx0 > right || idx1 < left)
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

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];
	}
	init(1, 0, N - 1);

	std::cin >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b;
		std::cin >> a >> b;
		if (a == 1)
		{
			int c;
			ull d;
			std::cin >> c >> d;
			update(1, 0, N - 1, b, c, d);
		}
		else
		{
			std::cout << query(1, 0, N - 1, b, b) << '\n';
		}
	}

	return 0;
}