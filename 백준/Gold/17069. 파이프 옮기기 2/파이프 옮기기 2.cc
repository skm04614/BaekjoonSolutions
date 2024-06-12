#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int HOR = 0;
constexpr int VER = 1;
constexpr int DIAG = 2;

int MAP[34][34];
int N;

unsigned long long DP[68][3][34][34];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> MAP[i][j];
		}
	}

	DP[0][HOR][0][1] = 1;

	unsigned long long result = 0;
	for (int n = 1; n < 2 * N; n++)
	{
		for (int y = 0; y < N; y++)
		{
			for (int x = 0; x < N; x++)
			{
				if (x - 1 >= 0)
				{
					DP[n][HOR][y][x] = DP[n - 1][HOR][y][x - 1] + DP[n - 1][DIAG][y][x - 1];
					if (MAP[y][x])
					{
						DP[n][HOR][y][x] = 0;
					}
				}

				if (y - 1 >= 0)
				{
					DP[n][VER][y][x] = DP[n - 1][VER][y - 1][x] + DP[n - 1][DIAG][y - 1][x];
					if (MAP[y][x])
					{
						DP[n][VER][y][x] = 0;
					}
				}

				if (x - 1 >= 0 && y - 1 >= 0)
				{
					DP[n][DIAG][y][x] = DP[n - 1][HOR][y - 1][x - 1] + DP[n - 1][VER][y - 1][x - 1] + DP[n - 1][DIAG][y - 1][x - 1];
					if (MAP[y][x] || MAP[y][x - 1] || MAP[y - 1][x])
					{
						DP[n][DIAG][y][x] = 0;
					}
				}
			}
		}
		result += DP[n][HOR][N - 1][N - 1] + DP[n][VER][N - 1][N - 1] + DP[n][DIAG][N - 1][N - 1];
	}
	std::cout << result;

	return 0;
}