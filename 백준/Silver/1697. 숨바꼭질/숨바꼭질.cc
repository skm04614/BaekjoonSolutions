#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>


int COST[100001];


struct
{
	int arr[1000001];
	int left = 0;
	int right = 0;

	void push(int loc)
	{
		arr[right] = loc;
		right++;
	}

	int pop()
	{
		return arr[left++];
	}

	bool empty()
	{
		return left == right;
	}
} Q;


int N;
int K;

int main(void)
{
	scanf("%d %d", &N, &K);

	for (int i = 0; i < sizeof(COST) / sizeof(COST[0]); i++)
	{
		COST[i] = 0x7FFFFFFF;
	}
	
	COST[N] = 0;
	Q.push(N);

	int loc;
	while (!Q.empty())
	{
		loc = Q.pop();
		
		if (2 * loc <= 100000 && COST[2 * loc] == 0x7FFFFFFF)
		{
			COST[2 * loc] = COST[loc] + 1;
			Q.push(2 * loc);
		}
		
		if (loc - 1 >= 0 && COST[loc - 1] == 0x7FFFFFFF)
		{
			COST[loc - 1] = COST[loc] + 1;
			Q.push(loc - 1);
		}

		if (loc + 1 <= 100000 && COST[loc + 1] == 0x7FFFFFFF)
		{
			COST[loc + 1] = COST[loc] + 1;
			Q.push(loc + 1);
		}

		if (loc == K)
		{
			break;
		}
	}

	printf("%d", COST[loc]);



	return 0;
}