#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1010];
int TMP[1010];
int N;

inline void swap(int &x, int &y)
{
	int tmp = x;
	x = y;
	y = tmp;
}

void _merge_sort(int* arr, int* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;

	_merge_sort(arr, tmp, idx0, mid);
	_merge_sort(arr, tmp, mid + 1, idx1);

	int left = idx0;
	int right = mid + 1;
	int idx = 0;
	for (;;)
	{
		if (left > mid || right > idx1)
		{
			break;
		}

		if (arr[left] < arr[right])
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

	for (int i = 0; i <= (idx1 - idx0); i++)
	{
		arr[idx0 + i] = tmp[i];
	}
}

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

	_merge_sort(ARR, TMP, 0, N - 1);

	int sum = 0;
	for (int i = 0; i < N; i++)
	{
		sum += (N - i) * ARR[i];
	}
	std::cout << sum;

	return 0;
}