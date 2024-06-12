#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

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

		if (arr[left] < arr[right])
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

template <typename T>
int _bsearch(T* arr, int idx0, int idx1, T target)
{
	if (idx1 < idx0)
	{
		return 0;
	}

	int mid = (idx0 + idx1) / 2;
	if (arr[mid] == target)
	{
		return 1;
	}

	if (arr[mid] > target)
	{
		return _bsearch(arr, idx0, mid - 1, target);
	}
	else
	{
		return _bsearch(arr, mid + 1, idx1, target);
	}

	return false;
}

int ARR[100010];
int TMP[100010];
int N;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> ARR[i];
	}

	merge_sort(ARR, TMP, 0, N - 1);

	int m;
	int val;

	std::cin >> m;
	for (int i = 0; i < m; i++)
	{
		std::cin >> val;
		std::cout << _bsearch(ARR, 0, N - 1, val) << '\n';
	}

	return 0;
}