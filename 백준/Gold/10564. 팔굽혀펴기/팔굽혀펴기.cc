#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int DP[110][5050];
int ARR[11];
int N;
int S;

void init()
{
	for (int n = 0; n <= 100; ++n)
	{
		for (int s = 0; s <= S; ++s)
		{
			DP[n][s] = 0;
		}
	}
	DP[0][0] = 1;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int T;
	std::cin >> T;
	while (T--)
	{
		std::cin >> S >> N;
		for (int i = 1; i <= N; ++i)
		{
			std::cin >> ARR[i];
		}

		init();
		for (int n = 1; n <= 100; ++n)
		{
			for (int s = 0; s <= S; ++s)
			{
				if (DP[n - 1][s] == 0)
				{
					continue;
				}

				for (int i = 1; i <= N; ++i)
				{
					const int ns = s + n * ARR[i];
					if (ns > S)
					{
						continue;
					}

					DP[n][ns] = max(DP[n][ns], DP[n - 1][s] + ARR[i]);
				}
			}
		}

		int res = 0;
		for (int n = 1; n <= 100; ++n)
		{
			res = max(res, DP[n][S]);
		}
		std::cout << (res - 1) << '\n';
	}

	return 0;
}