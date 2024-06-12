#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


using ll = long long;
constexpr ll MOD = 1000000007;

ll ARR[1000100];
ll SEG_TREE[4000400];
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

	SEG_TREE[node] = (SEG_TREE[2 * node] * SEG_TREE[2 * node + 1]) % MOD;
}

void change(int node, int idx0, int idx1, int target_idx, ll target_val)
{
	if (target_idx < idx0 || target_idx > idx1)
	{
		return;
	}

	if (idx0 == idx1)
	{
		SEG_TREE[node] = target_val;
		return;
	}

	int mid = (idx0 + idx1) / 2;
	change(2 * node, idx0, mid, target_idx, target_val);
	change(2 * node + 1, mid + 1, idx1, target_idx, target_val);

	SEG_TREE[node] = (SEG_TREE[2 * node] * SEG_TREE[2 * node + 1]) % MOD;
}

ll query(int node, int idx0, int idx1, int left, int right)
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
	return (query(2 * node, idx0, mid, left, right) * query(2 * node + 1, mid + 1, idx1, left, right)) % MOD;
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
			change(1, 1, N, b, c);
		}
		else
		{
			std::cout << query(1, 1, N, b, c) << '\n';
		}
	}

	return 0;
}