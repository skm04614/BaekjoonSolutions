#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int SOL[15][15];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	for (int i = 0; i <= 14; i++)
	{
		SOL[0][i] = i;
	}

	for (int lv = 1; lv <= 14; lv++)
	{
		for (int i = 1; i <= 14; i++)
		{
			SOL[lv][i] = SOL[lv - 1][i] + SOL[lv][i - 1];
		}
	}

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		int k, n;
		std::cin >> k >> n;

		std::cout << SOL[k][n] << '\n';
	}


	return 0;
}