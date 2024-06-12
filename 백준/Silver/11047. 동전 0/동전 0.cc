#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int COINS[11];
int N, K;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> K;
	for (int i = 0; i < N; i++)
	{
		std::cin >> COINS[i];
	}

	int cnt = 0;
	for (int i = N - 1; i >= 0 && K; i--)
	{
		if (K < COINS[i])
		{
			continue;
		}

		cnt += (K / COINS[i]);
		K %= COINS[i];
	}

	std::cout << cnt;


	return 0;
}