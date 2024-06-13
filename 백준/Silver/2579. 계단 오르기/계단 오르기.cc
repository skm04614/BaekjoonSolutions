#include <cstdio>

int gRecord[2][301] = {};

int max(const int& n, const int& m)
{
	return n > m ? n : m;
}

int main(void)
{
	int N = 0;
	scanf("%d", &N);

	int score = 0;
	scanf("%d", &score);
	gRecord[0][1] = score;
	for (int i = 2; i <= N; i++)
	{
		scanf("%d", &score);
		gRecord[0][i] = score + max(gRecord[0][i - 2], gRecord[1][i - 2]);
		gRecord[1][i] = score + gRecord[0][i - 1];
	}

	printf("%d", max(gRecord[0][N], gRecord[1][N]));

	return 0;
}