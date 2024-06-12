#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull DP[110] = { 0, 1, 2 };
ull AC[110] = { 0, 0, 0 };

inline ull max(ull n, ull m)
{
	return n > m ? n : m;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	for (int n = 3; n <= 100; n++)
	{
		AC[n] = DP[n - 2];

		DP[n] = DP[n - 1] + 1;
		for (int i = 1; i <= n - 2; i++)
		{
			DP[n] = max(DP[n], DP[n - 2 - i] + i * AC[n - i]);
		}
	}

	int N;
	std::cin >> N;
	std::cout << DP[N];

	return 0;
}