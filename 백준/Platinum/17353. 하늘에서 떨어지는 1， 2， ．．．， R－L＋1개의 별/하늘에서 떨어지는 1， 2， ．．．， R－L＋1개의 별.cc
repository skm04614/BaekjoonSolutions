#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[100100];
ull SEG_TREE[400400];
ull LAZY[400400];
int N;

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		SEG_TREE[node] += LAZY[node] * (idx1 - idx0 + 1);
		if (idx0 != idx1)
		{
			LAZY[node << 1] += LAZY[node];
			LAZY[node << 1 | 1] += LAZY[node];
		}
		LAZY[node] = 0;
	}
}

void update(int node, int idx0, int idx1, int left, int right, int k)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		LAZY[node] = k;
		propagate(node, idx0, idx1);
		return;
	}

	int mid = (idx0 + idx1) >> 1;
	update(node << 1, idx0, mid, left, right, k);
	update(node << 1 | 1, mid + 1, idx1, left, right, k);

	SEG_TREE[node] = SEG_TREE[node << 1] + SEG_TREE[node << 1 | 1];
}

ull query(int node, int idx0, int idx1, int left, int right)
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

	int mid = (idx0 + idx1) >> 1;
	return query(node << 1, idx0, mid, left, right) + query(node << 1 | 1, mid + 1, idx1, left, right);
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

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int opt;
		std::cin >> opt;
		if (opt == 1)
		{
			int left, right;
			std::cin >> left >> right;
			update(1, 1, N, left, right, 1);
			update(1, 1, N, right + 1, right + 1, -(right - left + 1));
		}
		else
		{
			int x;
			std::cin >> x;
			std::cout << ARR[x] + query(1, 1, N, 1, x) << '\n';
		}
	}

	return 0;
}