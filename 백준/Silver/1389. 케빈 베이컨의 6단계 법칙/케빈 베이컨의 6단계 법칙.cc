#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int D[101][101];
int N;
int M;

int min(int n, int m)
{
	return n < m ? n : m;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (register int i = 1; i <= N; i++)
	{
		for (register int j = 1; j <= N; j++)
		{
			D[i][j] = (i == j ? 0 : INF);
		}
	}

	for (register int i = 0; i < M; i++)
	{
		int src, dest;
		std::cin >> src >> dest;

		D[src][dest] = D[dest][src] = 1;
	}

	for (register int k = 1; k <= N; k++)
	{
		for (register int i = 1; i <= N; i++)
		{
			for (register int j = 1; j <= N; j++)
			{
				
				if (D[i][k] == INF || D[k][j] == INF)
				{
					continue;
				}

				D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
			}
		}
	}

	int min = INF;
	int sol = 0;
	for (register int i = 1; i <= N; i++)
	{
		register int sum = 0;
		for (register int j = 1; j <= N; j++)
		{
			sum += (D[i][j] == INF ? 0 : D[i][j]);
		}

		if (sum < min)
		{
			min = sum;
			sol = i;
		}
	}
	std::cout << sol;

	return 0;
}