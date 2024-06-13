#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;


inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Seg
{
	int tree[800800];
	int bias;

	Seg() : tree{}, bias{ 1 }
	{

	}

	void init(int n)
	{
		for (bias = 1; bias <= n; bias <<= 1);
		--bias; // 1-based entries
	}

	void update(int idx, int val)
	{
		idx += bias;
		tree[idx] = val;

		while (idx >>= 1)
		{
			tree[idx] = max(tree[idx << 1], tree[idx << 1 | 1]);
		}
	}

	int query(int left, int right)
	{
		left += bias;
		right += bias;

		int res = 0;
		while (left <= right)
		{
			if (left & 1)
			{
				res = max(res, tree[left++]);
			}

			if (~right & 1)
			{
				res = max(res, tree[right--]);
			}

			left >>= 1, right >>= 1;
		}

		return res;
	}
} SEG;

int L[200200];
int R[200200];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	while (T--)
	{
		int n;
		std::cin >> n;
		SEG.init(n);
		for (int i = 1; i <= n; ++i)
		{
			L[i] = INF;
			R[i] = 0;
		}

		for (int i = 1; i <= n; ++i)
		{
			int val;
			std::cin >> val;
			L[val] = min(L[val], i);
			R[val] = max(R[val], i);

			SEG.update(i, val);
		}

		bool is_odd_array = true;
		for (int i = 1; i <= n; ++i)
		{
			if (L[i] > R[i])
			{
				continue;
			}

			if (SEG.query(L[i], R[i]) > i)
			{
				is_odd_array = false;
				break;
			}
		}

		std::cout << (is_odd_array ? "Yes" : "No") << '\n';
	}

	return 0;
}