#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int D[110][110];
int N;

int min(int x, int y)
{
	return x < y ? x : y;
}

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
			std::cin >> D[i][j];
			if (D[i][j])
			{
				D[i][j] = 1;
			}
			else
			{
				D[i][j] = INF;
			}
		}
	}
	
	for (int k = 0; k < N; k++)
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				if (D[i][k] == INF || D[k][j] == INF)
				{
					continue;
				}

				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << ((D[i][j] == INF || D[i][j] == 0) ? 0 : 1) << ' ';
		}
		std::cout << '\n';
	}


	return 0;
}