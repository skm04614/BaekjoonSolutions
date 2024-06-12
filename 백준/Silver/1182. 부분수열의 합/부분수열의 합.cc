#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int ARR[21];
int N;
int CNT;
int TARGET;

void sol(int sum, int sidx)
{
	if (sidx != 0 && sum == TARGET)
	{
		CNT++;
	}

	if (sidx > N)
	{
		return;
	}

	for (int idx = sidx; idx < N; idx++)
	{
		sol(sum + ARR[idx], idx + 1);
	}
}

int main(void)
{
	scanf("%d %d", &N, &TARGET);
	for (int i = 0; i < N; i++)
	{
		scanf("%d", &ARR[i]);
	}

	sol(0, 0);
	printf("%d", CNT);

	return 0;
}