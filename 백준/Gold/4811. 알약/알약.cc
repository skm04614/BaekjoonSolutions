#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

using ull = unsigned long long;
ull DP[100][100];

ull PRIMES[40001];
ull P;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	DP[0][0] = 1;
	for (int day = 1; day <= 60; day++)
	{
		for (int half_cnt = 0; half_cnt <= 30; half_cnt++)
		{
			DP[half_cnt][day] = DP[half_cnt + 1][day - 1];

			if (half_cnt)
			{
				DP[half_cnt][day] += DP[half_cnt - 1][day - 1];
			}
		}
	}

	for (;;)
	{
		int cnt;
		std::cin >> cnt;
		if (cnt == 0)
		{
			break;
		}

		std::cout << DP[0][2 * cnt] << '\n';
	}



	return 0;
}