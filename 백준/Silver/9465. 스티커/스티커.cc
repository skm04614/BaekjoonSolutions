#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

int T;
int DP[3][100001];
int STICKERS[2][100001];
int N;


inline int max(int x, int y)
{
	return x > y ? x : y;
}

int main(void)
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &N);
		for (int i = 0; i < 2; i++)
		{
			for (int n = 1; n <= N; n++)
			{
				scanf("%d", &STICKERS[i][n]);
			}
;		}

		for (int n = 1; n <= N; n++)
		{

			DP[0][n] = max(DP[1][n - 1], DP[2][n - 1]) + STICKERS[0][n];
			DP[1][n] = max(DP[0][n - 1], DP[2][n - 1]) + STICKERS[1][n];
			DP[2][n] = max(max(DP[0][n - 1], DP[1][n - 1]), DP[2][n - 1]);
		}
		printf("%d\n", max(max(DP[0][N], DP[1][N]), DP[2][N]));
	}

	return 0;
}