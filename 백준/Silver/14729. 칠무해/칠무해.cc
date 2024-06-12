#include <cstdio>

void swap(float& f1, float& f2)
{
	float tmp = f1;
	f1 = f2;
	f2 = tmp;
}

struct Heap
{
	int size;
	float records[10000002];

	void push(float val)
	{
		records[++size] = val;

		int curr = size;
		for (;;)
		{
			if (curr == 1 || records[curr / 2] <= records[curr])
			{
				return;
			}
			swap(records[curr / 2], records[curr]);
			curr /= 2;
		}
	}

	float pop(void)
	{
		float ret = records[1];
		records[1] = records[size--];

		int curr = 1;
		int child{};
		for (;;)
		{
			child = 2 * curr;
			if (size >= child + 1 && records[child + 1] < records[child])
			{
				child++;
			}

			if (size < child || records[curr] <= records[child])
			{
				break;
			}

			swap(records[curr], records[child]);
			curr = child;
		}
		return ret;
	}
} GHeap;

int main(void)
{
	int N{};
	float score{};

	scanf("%d", &N);
	for (int i = 0; i < N; i++)
	{
		scanf("%f", &score);
		GHeap.push(score);
	}

	for (int i = 0; i < 7; i++)
	{
		printf("%.3f\n", GHeap.pop());
	}

	return 0;
}