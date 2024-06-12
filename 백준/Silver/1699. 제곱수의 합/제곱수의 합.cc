#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int RECORD[100001];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main(void)
{
	int N;
	scanf("%d", &N);

	RECORD[0] = 0;
	RECORD[1] = 1;

	for (int n = 2; n <= N; n++)
	{
		RECORD[n] = 0x7FFFFFFF;
		for (int i = 1; ; i++)
		{
			int sq = i * i;
			if (sq == n)
			{
				RECORD[n] = 1;
				break;
			}
			else if (sq > n)
			{
				break;
			}

			RECORD[n] = min(RECORD[n], RECORD[sq] + RECORD[n - sq]);
		}
	}

	printf("%d", RECORD[N]);

	return 0;
}
