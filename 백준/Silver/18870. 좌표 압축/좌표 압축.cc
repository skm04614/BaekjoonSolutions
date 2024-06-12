#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ORIGINAL[1000100];
int ARR[1000100];
int N;

inline void __swap(int& n, int& m)
{
	int tmp = n;
	n = m;
	m = tmp;
}

int sort_and_unique(int* dest, const int* src, int size)
{
	int* heap = new int[size + 10] {};

	for (register int s = 1; s <= size; s++)
	{
		heap[s] = src[s];

		int c = s;
		while (c > 1)
		{
			int p = c >> 1;
			if (heap[p] <= heap[c])
			{
				break;
			}

			__swap(heap[p], heap[c]);
			c = p;
		}
	}

	int k = 0;
	for (register int s = size; s >= 1; s--)
	{
		int ret = heap[1];

		int max_s = s;
		__swap(heap[1], heap[max_s--]);

		int p = 1;
		while (p << 1 <= max_s)
		{
			int c = p << 1;
			if (c + 1 <= max_s && heap[c + 1] < heap[c])
			{
				++c;
			}

			if (heap[p] <= heap[c])
			{
				break;
			}

			__swap(heap[p], heap[c]);
			p = c;
		}

		if (k && ret == dest[k - 1])
		{
			continue;
		}

		dest[k++] = ret;
	}

	delete[] heap;

	return k;
}

int b_search(const int* arr, int idx0, int idx1, int k)
{
	for (;;)
	{
		int mid = (idx0 + idx1) >> 1;

		if (arr[mid] == k)
		{
			return mid;
		}

		if (arr[mid] > k)
		{
			idx1 = mid - 1;
		}
		else
		{
			idx0 = mid + 1;
		}
	}

	return -1;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (register int i = 1; i <= N; i++)
	{
		std::cin >> ORIGINAL[i];
	}
	
	int size = sort_and_unique(ARR, ORIGINAL, N);
	for (register int i = 1; i <= N; i++)
	{
		std::cout << b_search(ARR, 0, size - 1, ORIGINAL[i]) << ' ';
	}

	return 0;
}