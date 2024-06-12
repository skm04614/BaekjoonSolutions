#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
int map[1000][1000];

struct
{
	int dy;
	int dx;
} DIRS[4] = { {-1, 0}, {0, 1}, {1, 0}, {0, -1} };

int main(void)
{
	int n, m;
	scanf("%d %d", &n, &m);

	int sq = n * n;
	int Y = 0;
	int X = 0;
	int i = n / 2;
	int j = n / 2;
	int len = 1;
	int cnt = 0;
	int counter = 0;
	int dir_idx = 0;
	for (int val = 1; val <= sq; val++)
	{
		if (val == m)
		{
			Y = i;
			X = j;
		}

		map[i][j] = val;
		i += DIRS[dir_idx].dy;
		j += DIRS[dir_idx].dx;

		if (++cnt == len)
		{
			cnt = 0;
			dir_idx = (dir_idx + 1) % 4;
			if (++counter % 2 == 0)
			{
				len++;
			}
		}
	}

	for (int a = 0; a < n; a++)
	{
		for (int b = 0; b < n; b++)
		{
			printf("%d ", map[a][b]);
		}
		printf("\n");
	}
	printf("%d %d", Y + 1, X + 1);

	return 0;
}
