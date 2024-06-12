#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull DP[110][21];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	int val;
	std::cin >> N >> val;
	DP[0][val] = 1;

	for (int i = 1; i < N - 1; i++)
	{
		std::cin >> val;
		for (int tot = 0; tot <= 20; tot++)
		{
			if (DP[i - 1][tot] == 0)
			{
				continue;
			}

			if (tot + val <= 20)
			{
				DP[i][tot + val] += DP[i - 1][tot];
			}

			if (tot - val >= 0)
			{
				DP[i][tot - val] += DP[i - 1][tot];
			}
		}
	}
	std::cin >> val;
	std::cout << DP[N - 2][val];

	return 0;
}