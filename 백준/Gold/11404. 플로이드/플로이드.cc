#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x7FFFFFFFFFFFFFFF;

ull COST[110][110];
int N;

ull min(ull x, ull y)
{
	return x < y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			COST[i][j] = (i == j) ? 0 : INF;
		}
	}

	int M;
	std::cin >> M;
	for (int i = 0; i < M; i++)
	{
		int src, dest, cost;
		std::cin >> src >> dest >> cost;
		COST[src][dest] = min(COST[src][dest], cost);
	}

	for (int k = 1; k <= N; k++)
	{
		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				if (COST[i][k] < INF && COST[k][j] < INF)
				{
					COST[i][j] = min(COST[i][j], COST[i][k] + COST[k][j]);
				}
			}
		}
	}

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			std::cout << (COST[i][j] == INF ? 0 : COST[i][j]) << ' ';
		}
		std::cout << '\n';
	}


	return 0;
}