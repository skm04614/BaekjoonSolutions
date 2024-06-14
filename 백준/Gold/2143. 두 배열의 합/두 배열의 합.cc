#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
T max(T x, T y)
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

template <typename T>
int lbound(T* arr, int left, int right, T target)
{
	while (left <= right)
	{
		int mid = (left + right) >> 1;

		if (target <= arr[mid])
		{
			right = mid - 1;
		}
		else
		{
			left = mid + 1;
		}
	}

	return left;
}

template <typename T>
int rbound(T* arr, int left, int right, T target)
{
	while (left <= right)
	{
		int mid = (left + right) >> 1;

		if (target >= arr[mid])
		{
			left = mid + 1;
		}
		else
		{
			right = mid - 1;
		}
	}

	return right;
}

template <typename T>
int count(T* arr, int left, int right, T target)
{
	return max(rbound(arr, left, right, target) - lbound(arr, left, right, target) + 1, 0);
}

int S[2][1010];
int N[2];

int ARR[2][1001000];
int M[2];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int T;
	std::cin >> T;

	for (int i = 0; i < 2; ++i)
	{
		std::cin >> N[i];
		for (int j = 1; j <= N[i]; ++j)
		{
			int val;
			std::cin >> val;
			S[i][j] = val + S[i][j - 1];

			for (int k = 0; k < j; ++k)
			{
				ARR[i][++M[i]] = S[i][j] - S[i][k];
			}
		}

		if (i == 0)
		{
			msort(ARR[0], ARR[1], 1, M[i]);
		}
	}

	unsigned long long cnt = 0;
	for (int i = 1; i <= M[1]; ++i)
	{
		cnt += count(ARR[0], 1, M[0], T - ARR[1][i]);
	}
	std::cout << cnt;

	return 0;
}