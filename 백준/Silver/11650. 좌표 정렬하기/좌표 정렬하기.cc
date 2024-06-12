#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

class Point
{
public:
	Point()
		: Point{0, 0}
	{
	}

	Point(int x, int y)
		: x{x}, y{y}
	{
	}

	bool operator>(const Point& other) const
	{
		if (x == other.x)
		{
			return y < other.y;
		}

		return x < other.x;
	}

	void print() const
	{
		std::cout << x << ' ' << y << '\n';
	}

private:
	int x;
	int y;
};

Point ARR[100010];
Point TMP[100010];

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
void merge_sort(T* arr, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;

	merge_sort(arr, tmp, idx0, mid);
	merge_sort(arr, tmp, mid + 1, idx1);

	int left = idx0;
	int right = mid + 1;
	int i = 0;
	for (;;)
	{
		if (left > mid)
		{
			break;
		}

		if (right > idx1)
		{
			break;
		}

		if (arr[left] > arr[right])
		{
			tmp[i++] = arr[left++];
		}
		else
		{
			tmp[i++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		tmp[i++] = arr[left++];
	}

	while (right <= idx1)
	{
		tmp[i++] = arr[right++];
	}

	for (int j = 0; j < i; j++)
	{
		arr[idx0 + j] = tmp[j];
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;

	int x, y;
	for (int i = 0; i < n; i++)
	{
		std::cin >> x >> y;
		ARR[i] = Point{ x, y };
	}

	merge_sort(ARR, TMP, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		ARR[i].print();
	}

	return 0;
}