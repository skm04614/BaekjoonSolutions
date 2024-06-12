#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int ylim, int xlim) const
	{
		return y < 1 || y > ylim || x < 1 || x > xlim;
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}
};

Coords DIRS[4] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };
bool VISITED[0x100];
char MAP[22][22];
int R;
int C;
int SOL;

void sol(int cnt, const Coords current_pos)
{
	if (current_pos.is_out_of_bounds(R, C)
		|| VISITED[MAP[current_pos.y][current_pos.x]])
	{
		SOL = SOL > cnt ? SOL : cnt;
		return;
	}
	VISITED[MAP[current_pos.y][current_pos.x]] = true;

	for (int i = 0; i < 4; i++)
	{
		Coords new_pos = current_pos + DIRS[i];
		sol(cnt + 1, new_pos);
	}
	VISITED[MAP[current_pos.y][current_pos.x]] = false;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> R >> C;
	for (int r = 1; r <= R; r++)
	{
		std::cin >> MAP[r] + 1;
	}

	Coords start_pos = { 1, 1 };
	sol(0, start_pos);

	std::cout << SOL;

	return 0;
}