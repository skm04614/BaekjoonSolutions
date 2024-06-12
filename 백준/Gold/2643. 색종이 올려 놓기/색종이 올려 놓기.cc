#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Rect
{
	int dy;
	int dx;

	bool fits_in(const Rect& other) const
	{
		return (dy <= other.dy && dx <= other.dx) || (dy <= other.dx && dx <= other.dy);
	}

	bool operator>=(const Rect& other) const
	{
		return (dy * dx) >= (other.dy * other.dx);
	}

	bool operator<=(const Rect& other) const
	{
		return (dy * dx) <= (other.dy * other.dx);
	}
};

Rect ARR[110];
int N;

int DP[110];


inline int max(int n, int m)
{
	return n > m ? n : m;
}

template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
void _qsort(T* arr, int idx0, int idx1)
{
	if (idx0 >= idx1)
	{
		return;
	}

	int pivot = idx0;
	int left = pivot + 1;
	int right = idx1;
	for (;;)
	{
		while (left <= right && arr[right] <= arr[pivot])
		{
			right--;
		}

		while (left <= right && arr[left] >= arr[pivot])
		{
			left++;
		}

		if (left > right)
		{
			swap(arr[right], arr[pivot]);
			break;
		}

		swap(arr[left], arr[right]);
	}

	_qsort(arr, idx0, right - 1);
	_qsort(arr, right + 1, idx1);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 1; i <= N; i++)
	{
		std::cin >> ARR[i].dy >> ARR[i].dx;
	}
	_qsort(ARR, 1, N);

	ARR[0] = { 1100, 1100 };
	DP[0] = 0;

	int sol = 0;
	for (int i = 1; i <= N; i++)
	{
		for (int j = i - 1; j >= 0; j--)
		{
			if (ARR[i].fits_in(ARR[j]))
			{
				DP[i] = max(DP[i], DP[j] + 1);
			}
		}

		sol = max(sol, DP[i]);
	}
	std::cout << sol;

	return 0;
}