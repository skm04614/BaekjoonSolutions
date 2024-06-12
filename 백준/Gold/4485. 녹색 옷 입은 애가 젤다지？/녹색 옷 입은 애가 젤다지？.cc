#include <cstdio>

constexpr auto DIM = 125;
constexpr auto INF = 0xffffff;
int Map[DIM + 1][DIM + 1];
int MinCost[DIM + 1][DIM + 1];

const int DY[4] = { 1, 0, -1, 0 };
const int DX[4] = { 0, 1, 0, -1 };

struct Pair
{
	int y;
	int x;
} PairPool[DIM * DIM * DIM];

int BFS(int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			scanf("%d", &Map[i][j]);
			MinCost[i][j] = INF;
		}
	}
	MinCost[0][0] = Map[0][0];

	int idx = 0;
	int next = 0;
	PairPool[next++] = { 0, 0 };
	while (next > idx)
	{
		int y = PairPool[idx].y;
		int x = PairPool[idx].x;

		for (int i = 0; i < 4; i++)
		{
			int ny = y + DY[i];
			int nx = x + DX[i];

			if (ny < 0 || ny >= size || nx < 0 || nx >= size)
			{
				continue;
			}

			if (MinCost[ny][nx] > MinCost[y][x] + Map[ny][nx])
			{
				MinCost[ny][nx] = MinCost[y][x] + Map[ny][nx];
				PairPool[next++] = { ny, nx };
			}
		}
		idx++;
	}

	return MinCost[size - 1][size - 1];
}

int main(void)
{
	int tc = 0;
	for (;;)
	{
		int size = 0;
		scanf("%d", &size);
		if (size == 0) break;
		printf("Problem %d: %d\n", ++tc, BFS(size));
	}
	return 0;
}