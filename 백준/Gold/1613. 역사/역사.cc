#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int D[410][410];

int N, K;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	
	std::cin >> N >> K;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			D[i][j] = (i == j) ? 0 : INF;
		}
	}

	for (int i = 1; i <= K; i++)
	{
		int src, dest;
		std::cin >> src >> dest;
		D[src][dest] = 1;
	}

	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (D[i][k] == INF || D[k][j] == INF)
				{
					continue;
				}

				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int v1, v2;
		std::cin >> v1 >> v2;

		const int c1 = D[v1][v2];
		const int c2 = D[v2][v1];

		if (c1 != INF && c1 > 0)
		{
			std::cout << -1;
		}
		else if (c2 != INF && c2 > 0)
		{
			std::cout << 1;
		}
		else
		{
			std::cout << 0;
		}
		std::cout << '\n';
	}

	return 0;
}