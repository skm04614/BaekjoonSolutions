#include <cstdio>

int gRecord[32][1001];
int gPos[32][1001];

int main(void)
{
	int T, W, p;
	scanf("%d %d", &T, &W);
	gPos[0][0] = 1;

	for (int t = 1; t <= T; t++)
	{
		scanf("%d", &p);
		for (int w = 0; w <= W; w++)
		{
			if (gPos[w][t - 1] == 0) continue;

			if (p == gPos[w][t - 1])
			{
				if (gRecord[w][t] <= gRecord[w][t - 1] + 1)
				{
					gRecord[w][t] = gRecord[w][t - 1] + 1;
					gPos[w][t] = gPos[w][t - 1];
				}
			}
			else
			{
				if (gRecord[w][t] <= gRecord[w][t - 1])
				{
					gRecord[w][t] = gRecord[w][t - 1];
					gPos[w][t] = gPos[w][t - 1];
				}
				if (gRecord[w + 1][t] <= gRecord[w][t - 1] + 1)
				{
					gRecord[w + 1][t] = gRecord[w][t - 1] + 1;
					gPos[w + 1][t] = p;
				}
			}
		}
	}

	int sol = 0;
	for (int w = 0; w <= W; w++)
	{
		for (int t = 1; t <= T; t++)
		{
			sol = sol > gRecord[w][t] ? sol : gRecord[w][t];
		}
	}
	printf("%d", sol);
	return 0;
}