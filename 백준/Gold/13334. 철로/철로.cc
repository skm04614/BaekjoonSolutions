#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
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

struct Heap
{
	int data[100100];
	int _size;

	bool empty() const
	{
		return _size == 0;
	}

	int size() const
	{
		return _size;
	}

	const int& peek() const
	{
		return data[1];
	}

	void push(int v)
	{
		data[++_size] = v;

		int c = _size;
		while (c > 1)
		{
			int p = c >> 1;
			if (data[p] <= data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			c = p;
		}
	}

	int pop()
	{
		swap(data[1], data[_size--]);

		int p = 1;
		int c = p << 1;
		while (c <= _size)
		{
			if ((c | 1) <= _size && data[c | 1] <= data[c])
			{
				c |= 1;
			}

			if (data[p] <= data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			p = c;
			c = p << 1;
		}

		return data[_size + 1];
	}
} HQ;

struct Line
{
	int l;
	int r;

	bool operator<=(const Line& other) const
	{
		return r <= other.r;
	}
};

int X[100100];
int XTMP[100100];
Line ARR[100100];
Line TMP[100100];
int N;
int D;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> ARR[i].l >> ARR[i].r;
		if (ARR[i].l > ARR[i].r)
		{
			swap(ARR[i].l, ARR[i].r);
		}
		X[i] = ARR[i].l;
	}
	msort(ARR, TMP, 1, N);
	msort(X, XTMP, 1, N);

	std::cin >> D;

	int res = 0;
	int j = 1;
	for (int i = 1; i <= N; ++i)
	{
		int left = X[i];
		int right = left + D;

		for (; j <= N && ARR[j].r <= right; ++j)
		{
			HQ.push(ARR[j].l);
		}

		while (!HQ.empty() && HQ.peek() < left)
		{
			HQ.pop();
		}

		res = max(res, HQ.size());
	}
	std::cout << res;

	return 0;
}