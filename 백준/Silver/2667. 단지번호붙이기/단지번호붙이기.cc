#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


struct Coords
{
	int y;
	int x;

	bool is_out_of_bounds(int y0, int y1, int x0, int x1) const
	{
		return (y < y0 || y >= y1 || x < x0 || x >= x1);
	}

	Coords operator+(const Coords& other) const
	{
		return { y + other.y, x + other.x };
	}
};

bool VISITED[26][26];
int N;

int RECORD[3000];
int K;

const Coords DIRS[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };


int sol(const Coords& current_pos)
{
	if (VISITED[current_pos.y][current_pos.x]
		|| current_pos.is_out_of_bounds(0, N, 0, N))
	{
		return 0;
	}
	VISITED[current_pos.y][current_pos.x] = true;

	int cnt = 1;
	for (int i = 0; i < 4; i++)
	{
		const Coords new_pos = current_pos + DIRS[i];
		cnt += sol(new_pos);
	}

	return cnt;
}

void _insertion_sort(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int _i = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[_i])
			{
				_i = j;
			}
		}

		int tmp = arr[i];
		arr[i] = arr[_i];
		arr[_i] = tmp;
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			char c;
			std::cin >> c;
			if (c == '0')
			{
				VISITED[i][j] = true;
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			int res = sol({ i, j });
			if (res)
			{
				RECORD[K++] = res;
			}
		}
	}

	_insertion_sort(RECORD, K);
	std::cout << K << '\n';
	for (int i = 0; i < K; i++)
	{
		std::cout << RECORD[i] << '\n';
	}

	return 0;
}