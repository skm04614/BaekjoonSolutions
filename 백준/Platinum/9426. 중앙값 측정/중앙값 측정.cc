#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Seg
{
	int tree[1 << 17];
	int bias;

	void init(int n)
	{
		for (bias = 1; bias < n; bias <<= 1);
	}

	void add(int idx, int val)
	{
		idx += bias;
		tree[idx] += val;

		while (idx >>= 1)
		{
			tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
		}
	}

	int query(int idx0, int idx1)
	{
		idx0 += bias;
		idx1 += bias;

		int res = 0;
		while (idx0 <= idx1)
		{
			if (idx0 & 1)
			{
				res += tree[idx0++];
			}

			if (~idx1 & 1)
			{
				res += tree[idx1--];
			}

			idx0 >>= 1, idx1 >>= 1;
		}

		return res;
	}
} SEG;

int ARR[250250];
int N;
int K;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> ARR[i];
	}

	SEG.init(65536);
	for (int i = 0; i < K; ++i)
	{
		SEG.add(ARR[i], 1);
	}

	unsigned long long sol = 0;
	for (int i = K; i <= N; ++i)
	{
		SEG.add(ARR[i - K], -1);
		SEG.add(ARR[i], 1);

		int left = 0;
		int right = 65535;
		int target = (K + 1) >> 1;
		while (left <= right)
		{
			int mid = (left + right) >> 1;
			int cnt = SEG.query(0, mid);

			if (target > cnt)
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
		sol += left;
	}
	std::cout << sol;

	return 0;
}