#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int y_max, int x_max) const
	{
		return y < 0 || y >= y_max || x < 0 || x >= x_max;
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}
};

const Coords DMTX[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int MAP[51][51];
bool VISITED[51][51];
int N; // # rows / Y
int M; // # cols / X

int K;
Coords START_POINTS[2501];

int T;

void reset()
{
	for (int i = 0; i < 51; i++)
	{
		for (int j = 0; j < 51; j++)
		{
			MAP[i][j] = 0;
			VISITED[i][j] = false;
		}
	}
}

int _sol(const Coords start_point)
{
	if (VISITED[start_point.y][start_point.x]
		|| !MAP[start_point.y][start_point.x]
		|| start_point.is_out_of_bounds(N, M))
	{
		return 0;
	}
	VISITED[start_point.y][start_point.x] = 1;

	int sum = 1;
	for (int i = 0; i < 4; i++)
	{
		sum += _sol(start_point + DMTX[i]);
	}

	return sum;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		reset();

		std::cin >> M >> N >> K;
		for (int k = 0; k < K; k++)
		{
			int x, y;
			std::cin >> x >> y;

			MAP[y][x] = 1;
			START_POINTS[k] = { y, x };
		}

		int sol = 0;
		for (int k = 0; k < K; k++)
		{
			sol += _sol(START_POINTS[k]) > 0;
		}

		std::cout << sol << '\n';
	}

	return 0;
}