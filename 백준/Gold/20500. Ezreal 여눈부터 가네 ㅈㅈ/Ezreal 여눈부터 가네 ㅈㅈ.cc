#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull DP[3][1516];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;

	DP[2][1] = 1;
	for (int n = 2; n <= 1515; n++)
	{
		for (int i = 0; i < 3; i++)
		{
			DP[(i + 1) % 3][n] = (DP[(i + 1) % 3][n] + DP[i][n - 1]) % 1000000007;
			DP[(i + 5) % 3][n] = (DP[(i + 5) % 3][n] + DP[i][n - 1]) % 1000000007;
		}
	}

	std::cout << DP[0][N];

	return 0;
}