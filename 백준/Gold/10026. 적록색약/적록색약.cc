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

struct Queue
{
	Coords data[10100];
	int lp = -1;
	int rp = -1;

	void reset()
	{
		lp = rp = -1;
	}

	void push(const Coords c)
	{
		data[++rp] = c;
	}

	const Coords& pop()
	{
		return data[++lp];
	}

	bool empty() const
	{
		return lp == rp;
	}
};

const Coords DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

char MAP[110][110];
char MAP_ABN[110][110];
bool VISITED[110][110];
bool VISITED_ABN[110][110];
int N;

Queue Q, Q_ABN;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> MAP[i];
		for (int j = 0; j < N; j++)
		{
			MAP_ABN[i][j] = (MAP[i][j] == 'G' ? 'R' : MAP[i][j]);
		}
	}
	
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (VISITED[i][j])
			{
				continue;
			}

			cnt++;
			const Coords start_pos = { i, j };
			const char start_char = MAP[i][j];

			VISITED[start_pos.y][start_pos.x] = true;
			Q.push(start_pos);
			while (!Q.empty())
			{
				const Coords& current_pos = Q.pop();
				for (int i = 0; i < 4; i++)
				{
					const Coords next_pos = current_pos + DIRS[i];
					if (VISITED[next_pos.y][next_pos.x]
						|| MAP[next_pos.y][next_pos.x] != start_char)
					{
						continue;
					}

					VISITED[next_pos.y][next_pos.x] = true;
					Q.push(next_pos);
				}
			}
		}
	}

	int cnt_abn = 0;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (VISITED_ABN[i][j])
			{
				continue;
			}

			cnt_abn++;
			const Coords start_pos = { i, j };
			const char start_char = MAP_ABN[i][j];

			VISITED_ABN[start_pos.y][start_pos.x] = true;
			Q_ABN.push(start_pos);
			while (!Q_ABN.empty())
			{
				const Coords& current_pos = Q_ABN.pop();
				for (int i = 0; i < 4; i++)
				{
					const Coords next_pos = current_pos + DIRS[i];
					if (VISITED_ABN[next_pos.y][next_pos.x]
						|| MAP_ABN[next_pos.y][next_pos.x] != start_char)
					{
						continue;
					}

					VISITED_ABN[next_pos.y][next_pos.x] = true;
					Q_ABN.push(next_pos);
				}
			}
		}
	}

	std::cout << cnt << ' ' << cnt_abn;

	return 0;
}