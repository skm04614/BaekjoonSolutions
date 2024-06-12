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

const Coords DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

Coords Q[365000];
int L;
int R;

char MAP[610][610];
bool VISITED[610][610];
int Y;
int X;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> Y >> X;

	L = R = -1;
	for (int y = 0; y < Y; y++)
	{
		std::cin >> MAP[y];
		for (int x = 0; x < X; x++)
		{
			if (MAP[y][x] == 'I')
			{
				Q[++R] = { y, x };
				VISITED[y][x] = true;
			}
		}
	}

	int cnt = 0;
	while (L < R)
	{
		const Coords& current_pos = Q[++L];

		for (int i = 0; i < 4; i++)
		{
			const Coords new_pos = current_pos + DIRS[i];

			if (!new_pos.is_out_of_bounds(0, Y, 0, X)
				&& MAP[new_pos.y][new_pos.x] != 'X'
				&& !VISITED[new_pos.y][new_pos.x])
			{
				Q[++R] = new_pos;
				VISITED[new_pos.y][new_pos.x] = true;
				cnt += (MAP[new_pos.y][new_pos.x] == 'P');
			}
		}
	}

	if (cnt)
	{
		std::cout << cnt;
	}
	else
	{
		std::cout << "TT";
	}

	return 0;
}