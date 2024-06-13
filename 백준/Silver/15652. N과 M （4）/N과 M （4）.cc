#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int N, M;
int RECORD[8];

void sol(int depth, int snum)
{
	if (depth == M)
	{
		for (int m = 0; m < M; m++)
		{
			printf("%d ", RECORD[m]);
		}
		printf("\n");
		return;
	}
	for (int i = snum; i <= N; i++)
	{
		RECORD[depth] = i;
		sol(depth + 1, i);
	}
}

int main(void)
{
	scanf("%d %d", &N, &M);

	sol(0, 1);

	return 0;
}