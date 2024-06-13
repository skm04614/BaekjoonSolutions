#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int y0, int y1, int x0, int x1) const
	{
		return y > y1 || y < y0 || x > x1 || x < x0;
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}

	bool operator==(const Coords& other) const
	{
		return y == other.y && x == other.x;
	}
};

const Coords DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

struct Queue
{
	Coords data[1000001];
	int l = -1;
	int r = -1;

	bool empty() const
	{
		return l == r;
	}

	void push(const Coords c)
	{
		data[++r] = c;
	}

	Coords pop()
	{
		return data[++l];
	}
};

Queue Q;
int COST[1001][1001];
int R;
int C;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> R >> C;
	Coords start_pos;
	int val;
	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			std::cin >> val;
			if (val == 2)
			{
				start_pos.y = y;
				start_pos.x = x;
				COST[y][x] = 0;
			}
			else if (val == 0)
			{
				COST[y][x] = 0;
			}
			else
			{
				COST[y][x] = -1;
			}
		}
	}

	Q.push(start_pos);
	while (!Q.empty())
	{
		const Coords current_pos = Q.pop();

		for (int i = 0; i < 4; i++)
		{
			const Coords new_pos = current_pos + DIRS[i];
			if (new_pos.is_out_of_bounds(0, R - 1, 0, C - 1)
				|| COST[new_pos.y][new_pos.x] != -1)
			{
				continue;
			}

			COST[new_pos.y][new_pos.x] = COST[current_pos.y][current_pos.x] + 1;
			Q.push(new_pos);
		}
	}

	for (int y = 0; y < R; y++)
	{
		for (int x = 0; x < C; x++)
		{
			std::cout << COST[y][x] << ' ';
		}
		std::cout << '\n';
	}


	return 0;
}