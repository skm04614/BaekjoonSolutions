#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <cstdint>


int32_t ARR[10000010];
int32_t TMP[10000010];
int N;

void merge_sort(int32_t* src, int32_t* tmp, int idx0, int idx1)
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
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &ARR[i]);
	}

	merge_sort(ARR, TMP, 0, N - 1);

	for (int i = 0; i < N; i++)
	{
		printf("%d\n", ARR[i]);
	}


	return 0;
}