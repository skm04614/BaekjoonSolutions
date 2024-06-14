#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int MAP[101][101];
int VISITED[4][101][101];
int X, Y;

struct Coords
{
	int y;
	int x;
	int dir;

	void move()
	{
		if (dir == 0)
		{
			--y;
			return;
		}

		if (dir == 1)
		{
			--x;
			return;
		}

		if (dir == 2)
		{
			++y;
			return;
		}

		++x;
	}

	Coords rotate(int opt) const
	{
		return { y, x, (dir + 4 + (opt ? -1 : 1)) & 3};
	}

	bool is_out_of_bounds() const
	{
		return y < 0 || x < 0 || y >= Y || x >= X;
	}

	bool operator==(const Coords& other) const
	{
		return y == other.y && x == other.x;
	}
};

Coords START;
Coords END;

Coords Q[101 * 101 * 4];
int LP, RP;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> X >> Y;
	bool init_found = false;
	for (int i = 0; i < Y; ++i)
	{
		for (int j = 0; j < X; ++j)
		{
			char c;
			std::cin >> c;
			if (c == '.')
			{
				MAP[i][j] = 0;
			}
			else if (c == '*')
			{
				MAP[i][j] = 1;
			}
			else
			{
				(init_found ? END : START) = { i, j };
				init_found = true;
				MAP[i][j] = 0;
			}
		}
	}

	for (int dir = 0; dir < 4; ++dir)
	{
		VISITED[dir][START.y][START.x] = 1;
		Q[++RP] = { START.y, START.x, dir };
	}

	while (RP > LP)
	{
		Coords c = Q[++LP];
		const int cost = VISITED[c.dir][c.y][c.x];

		for (;;)
		{
			c.move();
			if (c.is_out_of_bounds() || MAP[c.y][c.x])
			{
				break;
			}

			if (VISITED[c.dir][c.y][c.x])
			{
				continue;
			}
			VISITED[c.dir][c.y][c.x] = cost;

			for (int opt = 0; opt < 2; ++opt)
			{
				const Coords n = c.rotate(opt);
				if (VISITED[n.dir][n.y][n.x])
				{
					continue;
				}

				VISITED[n.dir][n.y][n.x] = cost + 1;
				Q[++RP] = n;
			}
		}
	}

	int min_cost = INF;
	for (int dir = 0; dir < 4; ++dir)
	{
		if (!VISITED[dir][END.y][END.x])
		{
			continue;
		}

		min_cost = min(min_cost, VISITED[dir][END.y][END.x]);
	}
	std::cout << min_cost - 1;

	return 0;
}