#include <cstdio>

int arr[1000002];
int front;
int back;

int main(void)
{
	int N = 0;
	scanf("%d", &N);

	for (int i = 1; i <= N; i++)
	{
		arr[i] = i;
	}
	front = 1;
	back = N;

	for (;;)
	{
		if (front == back)
		{
			printf("%d", arr[front]);
			break;
		}

		front++;

		if (front == back)
		{
			printf("%d", arr[front]);
			break;
		}

		arr[++back] = arr[front++];
	}

	return 0;
}
