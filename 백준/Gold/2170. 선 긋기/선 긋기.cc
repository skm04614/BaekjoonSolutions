#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

template <typename T>
void msort(T* arr, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) >> 1;
	msort(arr, tmp, idx0, mid);
	msort(arr, tmp, mid + 1, idx1);

	int left = idx0;
	int right = mid + 1;
	int idx = 0;
	for (;;)
	{
		if (left > mid || right > idx1)
		{
			break;
		}

		if (arr[left] <= arr[right])
		{
			tmp[idx++] = arr[left++];
		}
		else
		{
			tmp[idx++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		tmp[idx++] = arr[left++];
	}

	while (right <= idx1)
	{
		tmp[idx++] = arr[right++];
	}

	for (int i = 0; i < idx; ++i)
	{
		arr[idx0 + i] = tmp[i];
	}
}

struct Line
{
	int l;
	int r;

	bool operator<=(const Line& other) const
	{
		if (l == other.l)
		{
			return r <= other.r;
		}

		return l < other.l;
	}

	int length() const
	{
		return r - l;
	}
};

Line ARR[1001000];
Line TMP[1001000];
int N;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> ARR[i].l >> ARR[i].r;
	}

	msort(ARR, TMP, 1, N);

	int res = 0;
	int idx = 1;
	while (idx <= N)
	{
		Line x = ARR[idx++];
		while (idx <= N && x.r >= ARR[idx].l)
		{
			x.r = max(x.r, ARR[idx++].r);
		}

		res += x.length();
	}
	std::cout << res;


	return 0;
}