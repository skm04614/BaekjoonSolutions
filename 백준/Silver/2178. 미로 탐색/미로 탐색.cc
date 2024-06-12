#include <cstdio>

char gMap[102][102]{};
int gCost[101][101]{};
int gR, gC;

constexpr int gDr[4] = { 1, 0, -1, 0 };
constexpr int gDc[4] = { 0, 1, 0, -1 };

struct Pos
{
	int y;
	int x;
} gQueue[10010];
constexpr Pos gD[4] = { {1, 0}, {0,1}, {-1, 0}, {0, -1} };
int gQLower{}, gQUpper{};

int main(void)
{
	scanf("%d %d", &gR, &gC);

	for (int r = 1; r <= gR; r++)
	{
		scanf("%s", gMap[r] + 1);
	}

	gCost[1][1] = 1;
	gQueue[gQUpper].y = 1;
	gQueue[gQUpper].x = 1;
	gQUpper++;

	while (gQUpper > gQLower)
	{
		const Pos& curr = gQueue[gQLower];
		if (curr.y == gR && curr.x == gC)
		{
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			Pos& next = gQueue[gQUpper];
			next.y = curr.y + gD[i].y;
			next.x = curr.x + gD[i].x;
			if (gMap[next.y][next.x] == '0' || gCost[next.y][next.x] > 0 
				|| next.y < 1 || next.y > gR || next.x < 1 || next.x > gC)
			{
				continue;
			}

			gCost[next.y][next.x] = gCost[curr.y][curr.x] + 1;
			gQUpper++;
		}
		gQLower++;
	}

	printf("%d", gCost[gR][gC]);

	return 0;
}