#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int y0, int y1, int x0, int x1) const
	{
		return y < y0 || y >= y1 || x < x0 || x >= x1;
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}
};

const Coords DIRS[4] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1} };

Coords Q[1000010];
int L = -1;
int R = -1;

int MAP[1001][1001];
int Y;
int X;
int TARGET_CNT;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> X >> Y;
	TARGET_CNT = Y * X;

	Coords start_pos;
	for (int y = 0; y < Y; y++)
	{
		for (int x = 0; x < X; x++)
		{
			std::cin >> MAP[y][x];
			if (MAP[y][x] == -1)
			{
				TARGET_CNT--;
			}
			else if (MAP[y][x] == 1)
			{
				start_pos = { y, x };
				Q[++R] = start_pos;
			}
		}
	}

	while (R > L)
	{
		const Coords& current_pos = Q[++L];

		for (int i = 0; i < 4; i++)
		{
			const Coords next_pos = current_pos + DIRS[i];
			if (!next_pos.is_out_of_bounds(0, Y, 0, X)
				&& MAP[next_pos.y][next_pos.x] == 0)
			{
				MAP[next_pos.y][next_pos.x] = MAP[current_pos.y][current_pos.x] + 1;
				Q[++R] = next_pos;
			}
		}
	}

	if (L == -1 || L + 1 != TARGET_CNT)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << MAP[Q[L].y][Q[L].x] - 1;
	}

	return 0;
}