#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

struct Seg
{
	int tree[1 << 17];
	int bias;

	Seg() : tree{}, bias{ 65536 }
	{
	}

	void update(int idx, int val)
	{
		idx += bias;
		tree[idx] += val;

		while (idx >>= 1)
		{
			tree[idx] = tree[idx << 1] + tree[idx << 1 | 1];
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
				res += tree[left++];
			}

			if (~right & 1)
			{
				res += tree[right--];
			}

			left >>= 1, right >>= 1;
		}

		return res;
	}
};

Seg SEG;

int ARR[250250];
int N;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int K;
	std::cin >> N >> K;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> ARR[i];
	}

	for (int i = 0; i < K; ++i)
	{
		SEG.update(ARR[i], 1);
	}

	const int k = (K + 1) / 2;
	ull sum = 0;
	for (int i = 0; i < N - K + 1; ++i)
	{
		int left = 0;
		int right = 65536;
		while (left <= right)
		{
			int mid = (left + right) >> 1;
			const int cnt = SEG.query(0, mid);

			if (k <= cnt)
			{
				right = mid - 1;
			}
			else
			{
				left = mid + 1;
			}
		}

		sum += left;
		SEG.update(ARR[i], -1);
		SEG.update(ARR[K + i], 1);
	}
	std::cout << sum;

	return 0;
}