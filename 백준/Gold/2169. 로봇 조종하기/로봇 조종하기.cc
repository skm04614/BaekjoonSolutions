#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

enum
{
	LEFT_DIAG = 0,
	RIGHT_DIAG = 1
};

constexpr int UNINITIALIZED = -0x7FFFFFFF;

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int DP[2][1010][1010];
int MAP[1010][1010];
int N, M;

struct Coords
{
	int y;
	int x;

	Coords left() const
	{
		return { y, x - 1 };
	}

	Coords right() const
	{
		return { y, x + 1 };
	}

	Coords up() const
	{
		return { y - 1, x };

	}

	bool is_out_of_bounds() const
	{
		return y <= 0 || y > N || x <= 0 || x > M;
	}
};

void init()
{
	for (int i = 0; i <= N + 1; ++i)
	{
		for (int j = 0; j <= M + 1; ++j)
		{
			for (int k = 0; k < 2; ++k)
			{
				DP[k][i][j] = UNINITIALIZED;
			}
		}
	}

	DP[0][1][1] = DP[1][1][1] = MAP[1][1];
}

int fill(const Coords c, int diag)
{
	if (c.is_out_of_bounds())
	{
		return UNINITIALIZED;
	}

	if (DP[diag][c.y][c.x] != UNINITIALIZED)
	{
		return DP[diag][c.y][c.x];
	}

	int v_l = fill(c.up(), LEFT_DIAG);
	int v_r = fill(c.up(), RIGHT_DIAG);
	int h = fill(diag ? c.right() : c.left(), diag);
	int tmp = max(max(v_l, v_r), h);

	if (tmp != UNINITIALIZED)
	{
		tmp += MAP[c.y][c.x];
	}

	return DP[diag][c.y][c.x] = max(DP[diag][c.y][c.x], tmp);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= M; ++j)
		{
			std::cin >> MAP[i][j];
		}
	}

	init();
	std::cout << fill({ N, M }, LEFT_DIAG);

	return 0;
}