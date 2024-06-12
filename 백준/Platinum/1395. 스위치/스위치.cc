#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int SEG_TREE[400400];
int LAZY[400400];
int N, M;

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		SEG_TREE[node] = (idx1 - idx0 + 1) - SEG_TREE[node];

		if (idx0 != idx1)
		{
			LAZY[2 * node] ^= 1;
			LAZY[2 * node + 1] ^= 1;
		}

		LAZY[node] = 0;
	}
}

void toggle(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx0 > right || idx1 < left)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		SEG_TREE[node] = (idx1 - idx0 + 1) - SEG_TREE[node];

		if (idx0 != idx1)
		{
			LAZY[2 * node] ^= 1;
			LAZY[2 * node + 1] ^= 1;
		}
		return;
	}

	int mid = (idx0 + idx1) / 2;
	toggle(2 * node, idx0, mid, left, right);
	toggle(2 * node + 1, mid + 1, idx1, left, right);
	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

int count(int node, int idx0, int idx1, int left, int right)
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
	return count(2 * node, idx0, mid, left, right) + count(2 * node + 1, mid + 1, idx1, left, right);
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 0)
		{
			toggle(1, 1, N, b, c);
		}
		else
		{
			std::cout << count(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}