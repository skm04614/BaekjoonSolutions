#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Coords
{
	int z;
	int y;
	int x;

	bool is_out_of_bounds(int z0, int z1, int y0, int y1, int x0, int x1) const
	{
		return z < z0 || z >= z1 || y < y0 || y >= y1 || x < x0 || x >= x1;
	}

	Coords operator+(const Coords& other) const
	{
		return { z + other.z, y + other.y, x + other.x };
	}
};

const Coords DIRS[6] = { {-1, 0, 0}, {1, 0, 0}, {0, -1, 0}, {0, 1, 0}, {0, 0, -1}, {0, 0, 1} };

Coords Q[1000010];
int L;
int R;

int MAP[101][101][101];
int Z;
int Y;
int X;
int TARGET_CNT;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> X >> Y >> Z;
	TARGET_CNT = Z * Y * X;
	L = R = -1;
	for (int z = 0; z < Z; z++)
	{
		for (int y = 0; y < Y; y++)
		{
			for (int x = 0; x < X; x++)
			{
				std::cin >> MAP[z][y][x];

				if (MAP[z][y][x] == -1)
				{
					TARGET_CNT--;
				}
				else if (MAP[z][y][x] == 1)
				{
					Q[++R] = { z, y, x };
				}
			}
		}
	}

	while (L < R)
	{
		const Coords& current_pos = Q[++L];

		for (int i = 0; i < 6; i++)
		{
			const Coords next_pos = current_pos + DIRS[i];
			if (!next_pos.is_out_of_bounds(0, Z, 0, Y, 0, X)
				&& MAP[next_pos.z][next_pos.y][next_pos.x] == 0)
			{
				MAP[next_pos.z][next_pos.y][next_pos.x] = MAP[current_pos.z][current_pos.y][current_pos.x] + 1;
				Q[++R] = next_pos;
			}
		}
	}

	std::cout << ((L + 1 != TARGET_CNT) ? -1 : MAP[Q[L].z][Q[L].y][Q[L].x] - 1);

	return 0;
}