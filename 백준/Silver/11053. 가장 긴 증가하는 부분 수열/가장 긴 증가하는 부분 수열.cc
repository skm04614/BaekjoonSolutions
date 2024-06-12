#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int ARR[1010];
int RECORD[1010];
int N;
int GMAX;

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int main(void)
{
	scanf("%d", &N);
	for (int i = 1; i <= N; i++)
	{
		scanf("%d", &ARR[i]);
	}

	
	for (int i = 1; i <= N; i++)
	{
		for (int j = 0; j < i; j++)
		{
			if (ARR[i] > ARR[j])
			{
				RECORD[i] = max(RECORD[i], RECORD[j] + 1);
				GMAX = GMAX > RECORD[i] ? GMAX : RECORD[i];
			}
		}
	}

	printf("%d", GMAX);

	return 0;
}