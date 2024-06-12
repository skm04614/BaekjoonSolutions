#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

constexpr bool HOR = true;
constexpr bool VER = false;

char MAP[60][60];
int VISITED[2][60][60];
int N;

struct Tree
{
	int y;
	int x;
	bool orientation;

	Tree move(int opt) const
	{
		switch (opt)
		{
		case 0:
			return move_up();
		case 1:
			return move_down();
		case 2:
			return move_left();
		case 3:
			return move_right();
		default:
			return rotate();
		}
	}

	bool is_out_of_bounds() const
	{
		if (orientation == HOR)
		{
			return y < 0 || x < 0 || y >= N || x + 2 >= N;
		}
		else
		{
			return y < 0 || x < 0 || y + 2 >= N || x >= N;
		}
	}

	bool is_invalid() const
	{
		if (is_out_of_bounds())
		{
			return true;
		}

		if (orientation == HOR)
		{
			return MAP[y][x] == '1' || MAP[y][x + 1] == '1' || MAP[y][x + 2] == '1';
		}
		else
		{
			return MAP[y][x] == '1' || MAP[y + 1][x] == '1' || MAP[y + 2][x] == '1';
		}
	}

	void set_visited(int cost) const
	{
		VISITED[orientation][y][x] = cost;
	}

	int get_visited() const
	{
		return VISITED[orientation][y][x];
	}

	bool is_visited() const
	{
		return VISITED[orientation][y][x] > 0;
	}

	bool can_rotate() const
	{
		if (orientation == HOR)
		{
			return !(move_up().is_invalid() || move_down().is_invalid());
		}
		else
		{
			return !(move_left ().is_invalid() || move_right().is_invalid());
		}
	}

	bool operator==(const Tree& other) const
	{
		return y == other.y && x == other.x && orientation == other.orientation;
	}

private:
	Tree move_up() const
	{
		return { y - 1, x, orientation };
	}

	Tree move_down() const
	{
		return { y + 1, x, orientation };
	}

	Tree move_left() const
	{
		return { y, x - 1, orientation };
	}

	Tree move_right() const
	{
		return { y, x + 1, orientation };
	}

	Tree rotate() const
	{
		if (!can_rotate())
		{
			return *this;
		}

		if (orientation == HOR)
		{
			return Tree{ y - 1, x + 1, VER };
		}
		else
		{
			return Tree{ y + 1, x - 1, HOR };
		}
	}
};

Tree Q[5500];
int LP;
int RP;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> MAP[i];
	}

	Tree start_tree;
	bool start_initialized = false;

	Tree end_tree;
	bool end_initialized = false;

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (!end_initialized && MAP[i][j] == 'E')
			{
				end_tree.y = i;
				end_tree.x = j;
				end_tree.orientation = MAP[i][j + 1] == 'E' ? HOR : VER;
				end_initialized = true;
			}
			else if (!start_initialized && MAP[i][j] == 'B')
			{
				start_tree.y = i;
				start_tree.x = j;
				start_tree.orientation = MAP[i][j + 1] == 'B' ? HOR : VER;
				start_initialized = true;
			}
		}
	}

	LP = RP = -1;
	start_tree.set_visited(1);
	Q[++RP] = start_tree;

	while (RP > LP)
	{
		const Tree& current_tree = Q[++LP];
		if (current_tree == end_tree)
		{
			std::cout << VISITED[current_tree.orientation][current_tree.y][current_tree.x] - 1;
			return 0;
		}

		for (int i = 0; i < 5; i++)
		{
			Tree next_tree = current_tree.move(i);
			if (next_tree.is_invalid() || next_tree.is_visited())
			{
				continue;
			}

			next_tree.set_visited(current_tree.get_visited() + 1);
 			Q[++RP] = next_tree;
		}
	}

	std::cout << 0;
	return 0;
}