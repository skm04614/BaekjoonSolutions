#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int TARGET;
int DP[50001];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> TARGET;

	for (int n = 1; n <= 50000; n++)
	{
		int min = 4;
		int candidate;
		for (int i = 1; i * i <= n; i++)
		{
			candidate = (DP[n - (i * i)]) + 1;
			min = min < candidate ? min : candidate;
			if (min == 1)
			{
				break;
			}
		}
		DP[n] = min;
	}
	std::cout << DP[TARGET];

	return 0;
}