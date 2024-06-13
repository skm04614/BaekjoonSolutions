#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int DP[2][10010];
int COINS[101];
int N;
int K;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> K;
	for (int n = 0; n < N; n++)
	{
		std::cin >> COINS[n];
	}

	int* dp_current = DP[0];
	int* dp_old = DP[1];

	for (int i = 0; i < N; i++)
	{
		const int& current_coin = COINS[i];
		if (current_coin > K)
		{
			continue;
		}

		int* tmp = dp_current;
		dp_current = dp_old;
		dp_old = tmp;
	
		for (int k = 1; k < current_coin; k++)
		{
			dp_current[k] = 0;
		}

		dp_current[current_coin] = 1;

		for (int k = current_coin + 1; k <= K; k++)
		{
			dp_current[k] = dp_current[k - current_coin] + dp_old[k - current_coin];
		}

		for (int k = 1; k <= K; k++)
		{
			dp_current[k] += dp_old[k];
		}
	}

	std::cout << dp_current[K];


	return 0;
}