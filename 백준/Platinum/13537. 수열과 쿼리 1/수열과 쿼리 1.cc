#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int N;

struct MergeSortTree
{
	int* seg_tree[400400];

	MergeSortTree() : seg_tree{}
	{

	}

	~MergeSortTree()
	{
		for (int i = 0; i < sizeof(seg_tree) / sizeof(seg_tree[0]); i++)
		{
			if (seg_tree[i])
			{
				delete[] seg_tree[i];
			}
		}
	}

	void init(int node, int idx0, int idx1, const int* arr)
	{
		if (idx0 == idx1)
		{
			seg_tree[node] = new int[1] {arr[idx0]};
			return;
		}

		int mid = (idx0 + idx1) / 2;
		init(2 * node, idx0, mid, arr);
		init(2 * node + 1, mid + 1, idx1, arr);

		seg_tree[node] = new int[idx1 - idx0 + 1] {};

		int* current_tree = seg_tree[node];
		int idx = 0;

		const int* left_tree = seg_tree[2 * node];
		int left = 0;
		const int left_max = mid - idx0;

		const int* right_tree = seg_tree[2 * node + 1];
		int right = 0;
		const int right_max = idx1 - (mid + 1);

		for (;;)
		{
			if (left > left_max || right > right_max)
			{
				break;
			}

			if (right_tree[right] < left_tree[left])
			{
				current_tree[idx++] = right_tree[right++];
			}
			else
			{
				current_tree[idx++] = left_tree[left++];
			}
		}

		while (left <= left_max)
		{
			current_tree[idx++] = left_tree[left++];
		}

		while (right <= right_max)
		{
			current_tree[idx++] = right_tree[right++];
		}
	}

	int query(int node, int idx0, int idx1, int left, int right, int k)
	{
		if (idx1 < left || right < idx0)
		{
			return 0;
		}

		if (left <= idx0 && idx1 <= right)
		{
			const int* current_tree = seg_tree[node];
			int lower = 0;
			int upper = idx1 - idx0;
			int mid;
			for (;;)
			{
				if (lower > upper)
				{
					break;
				}

				mid = (lower + upper) / 2;
				if (current_tree[mid] <= k)
				{
					lower = mid + 1;
				}
				else
				{
					upper = mid - 1;
				}
			}
			return (idx1 - idx0) - upper;
		}

		int mid = (idx0 + idx1) / 2;
		return query(2 * node, idx0, mid, left, right, k) + query(2 * node + 1, mid + 1, idx1, left, right, k);
	}
} MST;

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
	MST.init(1, 1, N, ARR);

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int a, b, c;
		std::cin >> a >> b >> c;
		std::cout << MST.query(1, 1, N, a, b, c) << '\n';
	}

	return 0;
}