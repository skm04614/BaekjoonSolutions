#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
	unsigned int t0;
	unsigned int t1;

	bool operator<(const Element& other) const
	{
		if (t1 == other.t1)
		{
			return t0 < other.t0;
		}

		return t1 < other.t1;
	}
};

Element POOL[100001];
Element TMP[100001];
int N;

template <typename T>
void _merge_sort(T* arr, T* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;
	_merge_sort(arr, tmp, idx0, mid);
	_merge_sort(arr, tmp, mid + 1, idx1);

	int idx = 0;
	int left = idx0;
	int right = mid + 1;
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

	for (int i = 0; i < idx; i++)
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
		std::cin >> POOL[i].t0 >> POOL[i].t1;
	}
	_merge_sort(POOL, TMP, 0, N - 1);

	int cnt = 1;
	const Element* current = &POOL[0];
	for (int i = 1; i < N; i++)
	{
		const Element* next = &POOL[i];

		if (current->t1 <= next->t0)
		{
			cnt++;
			current = next;
		}
	}

	std::cout << cnt;

	return 0;
}