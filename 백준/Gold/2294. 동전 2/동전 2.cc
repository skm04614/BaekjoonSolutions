#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int DP[100010];
int COINS[101];

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N, M;
	std::cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		std::cin >> COINS[i];
		DP[COINS[i]] = 1;
	}

	for (int m = 1; m <= M; m++)
	{
		for (int i = 0; i < N; i++)
		{
			if (COINS[i] >= m || DP[m - COINS[i]] == 0)
			{
				continue;
			}

			if (DP[m])
			{
				DP[m] = min(DP[m], DP[m - COINS[i]] + DP[COINS[i]]);
			}
			else
			{
				DP[m] = DP[m - COINS[i]] + DP[COINS[i]];
			}
		}
	}

	std::cout << (DP[M] ? DP[M] : -1);

	return 0;
}