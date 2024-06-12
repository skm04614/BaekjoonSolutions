#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull DP[2][10010];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	while (T--)
	{
		int N;
		std::cin >> N;

		for (int sum = 0; sum <= 10000; sum++)
		{
			DP[0][sum] = 0;
		}
		int c = 1;
		int p = 0;

		for (int i = 0; i < N; i++)
		{
			int val;
			std::cin >> val;

			for (int sum = 0; sum < val; sum++)
			{
				DP[c][sum] = DP[p][sum];
			}

			DP[c][val] = DP[p][val] + 1;

			for (int sum = val + 1; sum <= 10000; sum++)
			{
				DP[c][sum] = DP[p][sum] + DP[c][sum - val];
			}

			p ^= 1;
			c ^= 1;
		}

		int TARGET;
		std::cin >> TARGET;
		std::cout << DP[p][TARGET] << '\n';
	}

	return 0;
}