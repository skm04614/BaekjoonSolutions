#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[110][110];
int N, M;
int CHEESE_CNT;

int VISIT_CNT[110][110];
int RECORD[110][110];

struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds() const
	{
		return y < 0 || x < 0 || y >= N || x >= M;
	}

	Coords move(int opt) const
	{
		switch (opt)
		{
		case 1:
			return { y + 1, x };
		case 2:
			return { y - 1, x };
		case 3:
			return { y, x + 1 };
		default:
			return { y, x - 1 };
		}
	}
};

Coords Q[10100];
int RP = -1;
int LP = -1;

Coords OUTER_CHEESE[10100];
int OC;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
		{
			std::cin >> MAP[i][j];
			CHEESE_CNT += MAP[i][j];
		}
	}

	Q[++RP] = { 0, 0 };
	RECORD[0][0] = 1;

	int sol;
	for (sol = 0; CHEESE_CNT; sol++)
	{
		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
				VISIT_CNT[i][j] = 0;
			}
		}

		LP = -1;
		RP = -1;
		Q[++RP] = { 0, 0 };
		RECORD[0][0] = sol + 1;

		OC = 0;

		while (RP > LP)
		{
			const Coords& current = Q[++LP];
			for (int i = 0; i < 4; i++)
			{
				Coords next = current.move(i);

				if (next.is_out_of_bounds() || RECORD[next.y][next.x] == RECORD[current.y][current.x])
				{
					continue;
				}

				if (MAP[next.y][next.x] == 0)
				{
					RECORD[next.y][next.x] = RECORD[current.y][current.x];
					Q[++RP] = next;
				}
				else if ((++VISIT_CNT[next.y][next.x]) == 2)
				{
					OUTER_CHEESE[OC++] = next;
				}
			}
		}

		for (int i = 0; i < OC; i++)
		{
			MAP[OUTER_CHEESE[i].y][OUTER_CHEESE[i].x] = 0;
			CHEESE_CNT--;
		}
	}
	std::cout << sol;

	return 0;
}