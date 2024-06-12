#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr int MAX_SIZE = 200000;
constexpr ull MOD = 1000000007;

struct Seg
{
	int cnt_tree[800800];
	ull sum_tree[800800];
	int bias;

	void init(int N)
	{
		for (bias = 1; bias < N; bias <<= 1);
	}

	void update(int val)
	{
		int idx = val + bias;
		++cnt_tree[idx];
		sum_tree[idx] += val;

		while (idx >>= 1)
		{
			cnt_tree[idx] = cnt_tree[idx << 1] + cnt_tree[idx << 1 | 1];
			sum_tree[idx] = sum_tree[idx << 1] + sum_tree[idx << 1 | 1];
		}
	}

	ull query_cnt(int left, int right)
	{
		left += bias;
		right += bias;

		int res = 0;
		while (left <= right)
		{
			if (left & 1)
			{
				res += cnt_tree[left++];
			}

			if (~right & 1)
			{
				res += cnt_tree[right--];
			}

			left >>= 1, right >>= 1;
		}

		return static_cast<ull>(res);
	}

	ull query_sum(int left, int right)
	{
		left += bias;
		right += bias;

		ull res = 0;
		while (left <= right)
		{
			if (left & 1)
			{
				res += sum_tree[left++];
			}

			if (~right & 1)
			{
				res += sum_tree[right--];
			}

			left >>= 1, right >>= 1;
		}

		return res;
	}
};

Seg SEG;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	SEG.init(MAX_SIZE);

	int n;
	std::cin >> n;
	
	int val;
	std::cin >> val;
	SEG.update(val);

	ull res = 1;
	for (int i = 0; i < n - 1; ++i)
	{
		std::cin >> val;

		ull left = SEG.query_cnt(0, val - 1) * val - SEG.query_sum(0, val - 1);
		ull right = SEG.query_sum(val + 1, 200000) - SEG.query_cnt(val + 1, 200000) * val;
		SEG.update(val);

		res = (res * ((left + right) % MOD)) % MOD;
	}
	std::cout << res;

	return 0;
}