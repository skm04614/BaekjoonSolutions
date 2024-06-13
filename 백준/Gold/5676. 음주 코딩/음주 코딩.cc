#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int SEG_TREE[400400];
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
	SEG_TREE[node] = SEG_TREE[2 * node] * SEG_TREE[2 * node + 1];
}

void change(int node, int idx0, int idx1, int target_idx, int target_val)
{
	if (target_idx > idx1 || target_idx < idx0)
	{
		return;
	}

	if (idx0 == idx1)
	{
		if (target_val > 0)
		{
			target_val = 1;
		}
		else if (target_val < 0)
		{
			target_val = -1;
		}

		SEG_TREE[node] = target_val;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	change(2 * node, idx0, mid, target_idx, target_val);
	change(2 * node + 1, mid + 1, idx1, target_idx, target_val);
	SEG_TREE[node] = SEG_TREE[2 * node] * SEG_TREE[2 * node + 1];
}

int query(int node, int idx0, int idx1, int left, int right)
{
	if (idx0 > right || idx1 < left)
	{
		return 1;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) / 2;
	return query(2 * node, idx0, mid, left, right) * query(2 * node + 1, mid + 1, idx1, left, right);
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	while (std::cin >> N >> M)
	{
		for (int i = 1; i <= N; i++)
		{
			std::cin >> ARR[i];
			if (ARR[i] > 0)
			{
				ARR[i] = 1;
			}
			else if (ARR[i] < 0)
			{
				ARR[i] = -1;
			}
		}
		init(1, 1, N);

		for (int i = 1; i <= M; i++)
		{
			char a;
			int b, c;
			std::cin >> a >> b >> c;
			if (a == 'C')
			{
				change(1, 1, N, b, c);
			}
			else
			{
				int result = query(1, 1, N, b, c);
				if (result > 0)
				{
					std::cout << '+';
				}
				else if (result < 0)
				{
					std::cout << '-';
				}
				else
				{
					std::cout << '0';
				}
			}
		}
		std::cout << '\n';
	}

	return 0;
}