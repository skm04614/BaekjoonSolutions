#include <cstdio>

int gRecord[3][1001];

inline int min(const int& n, const int& m)
{
	return n < m ? n : m;
}

int main(void)
{
	int N;
	scanf("%d", &N);
	scanf("%d %d %d", &gRecord[0][1], &gRecord[1][1], &gRecord[2][1]);
	for (int i = 2; i <= N; i++)
	{
		scanf("%d %d %d", &gRecord[0][i], &gRecord[1][i], &gRecord[2][i]);

		gRecord[0][i] += min(gRecord[1][i - 1], gRecord[2][i - 1]);
		gRecord[1][i] += min(gRecord[0][i - 1], gRecord[2][i - 1]);
		gRecord[2][i] += min(gRecord[0][i - 1], gRecord[1][i - 1]);
	}

	int sol = min(min(gRecord[0][N], gRecord[1][N]), gRecord[2][N]);
	printf("%d", sol);

	return 0;
}