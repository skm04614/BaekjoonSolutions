#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x2FFFFFFF;

inline int max(int x, int y)
{
	return x > y ? x : y;
}

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int W[210][210];
int N;

int V[210];
int H;

void init()
{
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 1; j <= N; ++j)
		{ 
			W[i][j] = (i == j) ? 0 : INF;
		}
	}
}

void floyd_warshall()
{
	for (int k = 1; k <= N; ++k)
	{
		for (int i = 1; i <= N; ++i)
		{
			for (int j = 1; j <= N; ++j)
			{
				if (W[i][k] == INF || W[k][j] == INF)
				{
					continue;
				}

				W[i][j] = min(W[i][j], W[i][k] + W[k][j]);
			}
		}
	}
}

void sol()
{
	int cities[210] = {};
	int n = 0;

	int val = INF;
	for (int k = 1; k <= N; ++k)
	{
		int tmp = 0;
		for (int i = 1; i <= H; ++i)
		{
			tmp = max(tmp, W[V[i]][k] + W[k][V[i]]);
			if (tmp >= INF)
			{
				break;
			}
		}

		if (tmp >= INF)
		{
			continue;
		}

		if (tmp < val)
		{
			n = 0;
			val = tmp;
		}

		if (tmp == val)
		{
			cities[++n] = k;
		}
	}

	for (int i = 1; i <= n; ++i)
	{
		std::cout << cities[i] << ' ';
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	init();

	int M;
	std::cin >> M;
	while (M--)
	{
		int u, v, w;
		std::cin >> u >> v >> w;
		W[u][v] = w;
	}

	std::cin >> H;
	for (int i = 1; i <= H; ++i)
	{
		std::cin >> V[i];
	}
	
	floyd_warshall();
	sol();

	return 0;
}