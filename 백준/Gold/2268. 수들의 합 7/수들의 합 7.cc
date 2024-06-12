#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

using ull = unsigned long long;
ull ARR[1001000];
ull SEG_TREE[4004000];
int N, M;

ull get_sum(int node, int idx0, int idx1, int left, int right)
{
	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return get_sum(2 * node, idx0, mid, left, right) + get_sum(2 * node + 1, mid + 1, idx1, left, right);
}

void modify(int node, int idx0, int idx1, int target_idx, int k)
{
	if (target_idx < idx0 || idx1 < target_idx)
	{
		return;
	}

	if (idx0 == idx1)
	{
		SEG_TREE[node] = k;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	modify(2 * node, idx0, mid, target_idx, k);
	modify(2 * node + 1, mid + 1, idx1, target_idx, k);

	SEG_TREE[node] = SEG_TREE[2 * node] + SEG_TREE[2 * node + 1];
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int m = 0; m < M; m++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		if (a == 0)
		{
			if (b > c)
			{
				int tmp = b;
				b = c;
				c = tmp;
			}
			std::cout << get_sum(1, 1, N, b, c) << '\n';
		}
		else
		{
			modify(1, 1, N, b, c);
		}
	}

	
	return 0;
}