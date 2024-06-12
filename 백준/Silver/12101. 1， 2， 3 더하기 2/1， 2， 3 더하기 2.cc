#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int T;
int N;
int K;
int CNT;
int DP[15];
int RECORD[15];

void sol(int depth, int sum)
{
	if (sum > N || CNT > K)
	{
		return;
	}

	if (sum == N)
	{
		if (++CNT == K)
		{
			if (K)
			{
				printf("%d", RECORD[0]);
			}
			for (int i = 1; i < depth; i++)
			{
				printf("+%d", RECORD[i]);
			}
			printf("\n");
		}

		return;
	}

	for (int v = 1; v <= 3; v++)
	{
		RECORD[depth] = v;
		sol(depth + 1, sum + v);
	}

}


int main(void)
{

	CNT = 0;
	scanf("%d", &N);

	DP[1] = 1;
	DP[2] = 2;
	DP[3] = 4;

	for (int n = 4; n <= N; n++)
	{
		DP[n] = DP[n - 1] + DP[n - 2] + DP[n - 3];
	}

	scanf("%d", &K);
	if (K > DP[N])
	{
		printf("-1\n");
	}
	else
	{
		sol(0, 0);
	}

	return 0;
}