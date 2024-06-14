#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int VISITED[51][51];
int MAP[51][51];
int N, M;

struct Coords
{
	int y;
	int x;

	Coords move(int opt, int step) const
	{
		if (opt == 0)
		{
			return { y + step, x };
		}

		if (opt == 1)
		{
			return { y - step, x };
		}

		if (opt == 2)
		{
			return { y, x + step };
		}

		return { y, x - step };
	}

	bool is_out_of_bounds() const
	{
		return y < 0 || y >= N || x < 0 || x >= M;
	}
};

int dfs(const Coords c, int depth)
{
	if (c.is_out_of_bounds() || MAP[c.y][c.x] == 0)
	{
		return 0;
	}

	if (depth > N * M)
	{
		return INF;
	}

	if (VISITED[c.y][c.x] > depth)
	{
		return VISITED[c.y][c.x];
	}

	VISITED[c.y][c.x] = ++depth;

	int deepest = depth;
	for (int i = 0; i < 4; ++i)
	{
		deepest = max(deepest, dfs(c.move(i, MAP[c.y][c.x]), depth));
	}

	return deepest;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	std::cin >> N >> M;
	for (int i = 0; i < N; ++i)
	{
		for (int j = 0; j < M; ++j)
		{
			char c;
			std::cin >> c;
			if (c == 'H')
			{
				MAP[i][j] = 0;
			}
			else
			{
				MAP[i][j] = c - '0';
			}
		}
	}

	int deepest = dfs({ 0, 0 }, 0);
	std::cout << (deepest == INF ? -1 : deepest);

	return 0;
}