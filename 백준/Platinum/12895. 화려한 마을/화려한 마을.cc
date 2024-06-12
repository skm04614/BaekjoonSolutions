#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull ARR[100100];
int N, T, Q;

ull SEG_TREE[400400];
ull LAZY[400400];

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		SEG_TREE[node] = LAZY[node];

		if (idx0 != idx1)
		{
			LAZY[2 * node] = LAZY[node];
			LAZY[2 * node + 1] = LAZY[node];
		}

		LAZY[node] = 0;
	}
}

void update(int node, int idx0, int idx1, int left, int right, int color)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		LAZY[node] = (1llu << color);
		propagate(node, idx0, idx1);
		return;
	}

	int mid = (idx0 + idx1) / 2;
	update(2 * node, idx0, mid, left, right, color);
	update(2 * node + 1, mid + 1, idx1, left, right, color);
	SEG_TREE[node] = SEG_TREE[2 * node] | SEG_TREE[2 * node + 1];
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

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, left, right) | query(2 * node + 1, mid + 1, idx1, left, right);
}

ull count(int node, int idx0, int idx1, int left, int right)
{
	ull result = query(node, idx0, idx1, left, right);
	ull cnt = 0;
	for (ull n = 1; n <= (1llu << T); n <<= 1)
	{
		if (result & n)
		{
			cnt++;
		}
	}
	return cnt;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> T >> Q;
	update(1, 1, N, 1, N, 1);
	for (int i = 1; i <= Q; i++)
	{
		char a;
		int b, c;
		std::cin >> a >> b >> c;

		if (b > c)
		{
			int tmp = b;
			b = c;
			c = tmp;
		}

		if (a == 'C')
		{
			int d;
			std::cin >> d;
			update(1, 1, N, b, c, d);
		}
		else
		{
			std::cout << count(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}