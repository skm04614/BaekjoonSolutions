#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 1000000;

enum
{
	LATE = 0,
	ABSENT = 1,
	ONTIME = 2
};

int DP[1010][2][3][3];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	DP[1][1][0][LATE] = DP[1][0][1][ABSENT] = DP[1][0][0][ONTIME] = 1;
	for (int d = 2; d <= 1000; ++d)
	{
		DP[d][1][0][LATE] = (DP[d - 1][0][0][ONTIME] + DP[d - 1][0][1][ABSENT] + DP[d - 1][0][2][ABSENT]) % MOD;

		for (int l = 0; l < 2; ++l)
		{
			DP[d][l][0][ONTIME] = (DP[d - 1][l][0][ONTIME] + DP[d - 1][l][1][ABSENT] + DP[d - 1][l][2][ABSENT]) % MOD;

			DP[d][l][1][ABSENT] = DP[d - 1][l][0][ONTIME];
			DP[d][l][2][ABSENT] = DP[d - 1][l][1][ABSENT];
		}
		DP[d][1][0][ONTIME] = (DP[d][1][0][ONTIME] + DP[d - 1][1][0][LATE]) % MOD;
		DP[d][1][1][ABSENT] = (DP[d][1][1][ABSENT] + DP[d - 1][1][0][LATE]) % MOD;
	}

	int n;
	std::cin >> n;
	
	int res = 0;
	for (int l = 0; l < 2; ++l)
	{
		for (int a = 0; a < 3; ++a)
		{
			for (int x = 0; x < 3; ++x)
			{
				res = (res + DP[n][l][a][x]) % MOD;
			}
		}
	}
	std::cout << res;

	return 0;
}