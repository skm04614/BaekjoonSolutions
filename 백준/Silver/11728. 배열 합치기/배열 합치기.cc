#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[2000100];
int TMP[2000100];
int N;

void m_sort(int* arr, int* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) >> 1;
	m_sort(arr, tmp, idx0, mid);
	m_sort(arr, tmp, mid + 1, idx1);

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

	for (int i = 0; i < idx; ++i)
	{
		arr[idx0 + i] = tmp[i];
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int n, m;
	std::cin >> n >> m;
	N = n + m;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> ARR[i];
	}

	m_sort(ARR, TMP, 0, N - 1);
	
	for (int i = 0; i < N; ++i)
	{
		std::cout << ARR[i] << ' ';
	}

	return 0;
}