#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull DP[2][1001000];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	int p = 0;
	int c = 1;
	int sq = 1;
	while (sq <= N)
	{
		for (int n = 0; n < sq; n++)
		{
			DP[c][n] = (DP[p][n]) % 1000000000;
		}

		DP[c][sq] = (1 + DP[p][sq]) % 1000000000;

		for (int n = sq + 1; n <= 1000000; n++)
		{
			DP[c][n] = (DP[p][n] + DP[c][n - sq]) % 1000000000;
		}

		sq *= 2;
		p ^= 1;
		c ^= 1;
	}

	std::cout << DP[p][N];

	return 0;
}