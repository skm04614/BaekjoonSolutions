#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int T[110][2];
int W[110][2];
int N;
int K;

int DP[110][100100];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> K;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> T[i][0] >> W[i][0] >> T[i][1] >> W[i][1];
	}

	DP[1][T[1][0]] = W[1][0];
	DP[1][T[1][1]] = W[1][1];
	for (int i = 2; i <= N; ++i)
	{
		for (int t = 1; t <= K; ++t)
		{
			if (DP[i - 1][t] == 0)
			{
				continue;
			}

			for (int j = 0; j < 2; ++j)
			{
				if (t + T[i][j] > K)
				{
					continue;
				}

				DP[i][t + T[i][j]] = max(DP[i][t + T[i][j]], DP[i - 1][t] + W[i][j]);
			}
		}
	}

	int res = 0;
	for (int t = 1; t <= K; ++t)
	{
		res = max(res, DP[N][t]);
	}
	std::cout << res;

	return 0;
}