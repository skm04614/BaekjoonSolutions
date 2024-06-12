#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstdint>

class Point
{
public:
	Point() : x{}, y{}
	{
	}

	Point(int x, int y) : x{ x }, y{y}
	{
	}

	void print() const
	{
		printf("%d %d\n", x, y);
	}

	bool operator<(const Point& other) const
	{
		if (y == other.y)
		{
			return x < other.x;
		}

		return y < other.y;
	}

private:
	int x;
	int y;
};

Point ARR[100010];
Point TMP[100010];


template <typename T>
void merge_sort(T* src, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;

	merge_sort(src, tmp, idx0, mid);
	merge_sort(src, tmp, mid + 1, idx1);

	int idx = 0;
	int left_idx = idx0;
	int right_idx = mid + 1;

	for (;;)
	{
		if (left_idx > mid
			|| right_idx > idx1)
		{
			break;
		}

		if (src[left_idx] < src[right_idx])
		{
			tmp[idx++] = src[left_idx++];
		}
		else
		{
			tmp[idx++] = src[right_idx++];
		}
	}

	while (left_idx <= mid)
	{
		tmp[idx++] = src[left_idx++];
	}

	while (right_idx <= idx1)
	{
		tmp[idx++] = src[right_idx++];
	}

	for (int i = 0; i < idx; i++)
	{
		src[idx0 + i] = tmp[i];
	}
}


int main(void)
{
	int n;
	scanf("%d", &n);

	int xval, yval;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &xval, &yval);
		ARR[i] = Point{ xval, yval };
	}

	merge_sort(ARR, TMP, 0, n - 1);

	for (int i = 0; i < n; i++)
	{
		ARR[i].print();
	}

	return 0;
}