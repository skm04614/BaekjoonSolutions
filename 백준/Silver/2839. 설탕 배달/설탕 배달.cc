#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int DP[5001];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int N;
	std::cin >> N;

	DP[3] = 1;
	DP[5] = 1;

	for (int n = 6; n <= N; n++)
	{
		int candidate1 = 0x7FFFFFFF;
		if (DP[n - 3] > 0)
		{
			candidate1 = DP[n - 3] + 1;
		}

		int candidate2 = 0x7FFFFFFF;
		if (DP[n - 5] > 0)
		{
			candidate2 = DP[n - 5] + 1;
		}

		DP[n] = candidate2 < candidate1 ? candidate2 : candidate1;
		if (DP[n] == 0x7FFFFFFF)
		{
			DP[n] = 0;
		}
	}

	std::cout << (DP[N] ? DP[N] : -1);

	return 0;
}