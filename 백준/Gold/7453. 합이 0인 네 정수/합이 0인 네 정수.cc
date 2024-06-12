#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int ARR_1[4010 * 4010];
int ARR_2[4010 * 4010];
int K;

inline void __swap(int& n, int& m)
{
	int tmp = n;
	n = m;
	m = tmp;
}

void __heapify(int* arr, int size)
{
	for (register int s = 1; s <= size; s++)
	{
		int c = s;
		while (c > 1)
		{
			int p = c >> 1;
			if (arr[c] <= arr[p])
			{
				break;
			}

			__swap(arr[c], arr[p]);
			c = p;
		}
	}
}

void heap_sort(int* arr, int size)
{
	__heapify(arr, size);

	for (register int s = size; s >= 1; s--)
	{
		int max_s = s;
		__swap(arr[1], arr[max_s--]);

		int p = 1;
		while (p << 1 <= max_s)
		{
			int c = p << 1;
			if (c + 1 <= max_s && arr[c + 1] > arr[c])
			{
				++c;
			}

			if (arr[c] <= arr[p])
			{
				break;
			}

			__swap(arr[p], arr[c]);
			p = c;
		}
	}
}

int __lower_bound(int* arr, int idx0, int idx1, int k)
{
	while (idx0 <= idx1)
	{
		int mid = (idx0 + idx1) >> 1;

		if (idx1 < idx0)
		{
			break;
		}

		if (arr[mid] >= k)
		{
			idx1 = mid - 1;
		}
		else
		{
			idx0 = mid + 1;
		}
	}

	return idx1 + 1;
}

int __upper_bound(int* arr, int idx0, int idx1, int k)
{
	while (idx0 <= idx1)
	{
		int mid = (idx0 + idx1) >> 1;

		if (idx1 < idx0)
		{
			break;
		}

		if (arr[mid] <= k)
		{
			idx0 = mid + 1;
		}
		else
		{
			idx1 = mid - 1;
		}
	}

	return idx0 - 1;
}

int count(int* arr, int idx0, int idx1, int k)
{
	int cnt = __upper_bound(arr, idx0, idx1, k) - __lower_bound(arr, idx0, idx1, k) + 1;
	return cnt < 0 ? 0 : cnt;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	std::cin >> N;

	int* arr[4]{};
	for (register int i = 0; i < 4; i++)
	{
		arr[i] = new int[N + 1] {};
	}

	for (register int i = 0; i < N; i++)
	{
		std::cin >> arr[0][i] >> arr[1][i] >> arr[2][i] >> arr[3][i];
	}

	for (register int i = 0; i < N; i++)
	{
		for (register int j = 0; j < N; j++)
		{
			++K;
			ARR_1[K] = arr[0][i] + arr[1][j];
			ARR_2[K] = arr[2][i] + arr[3][j];
		}
	}

	for (register int i = 0; i < 4; i++)
	{
		delete[] arr[i];
		arr[i] = nullptr;
	}

	heap_sort(ARR_1, K);
	heap_sort(ARR_2, K);

	unsigned long long sol = 0;
	for (register int i = 1; i <= K; i++)
	{
		sol += count(ARR_2, 1, K, -ARR_1[i]);
	}
	std::cout << sol;

	return 0;
}