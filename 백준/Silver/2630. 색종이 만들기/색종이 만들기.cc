#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int MAP[129][129];
int N;
int BLUE;
int WHITE;

void sol(int y0, int y1, int x0, int x1)
{
	if (x0 == x1 || y0 == y1)
	{
		if (MAP[y0][x0] == 0)
		{
			BLUE++;
		}
		else
		{
			WHITE++;
		}
		return;
	}

	for (int y = y0; y <= y1; y++)
	{
		for (int x = x0; x <= x1; x++)
		{
			if (MAP[y][x] != MAP[y0][x0])
			{
				int y_mid = (y0 + y1) / 2;
				int x_mid = (x0 + x1) / 2;

				sol(y0, y_mid, x0, x_mid);
				sol(y_mid + 1, y1, x0, x_mid);
				sol(y0, y_mid, x_mid + 1, x1);
				sol(y_mid + 1, y1, x_mid + 1, x1);
				return;
			}
		}
	}

	if (MAP[y0][x0] == 0)
	{
		BLUE++;
	}
	else
	{
		WHITE++;
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
			std::cin >> MAP[i][j];
		}
	}
	
	sol(0, N - 1, 0, N - 1);

	std::cout << BLUE << '\n' << WHITE;


	
	return 0;
}