#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

using ull = unsigned long long;

constexpr ull MOD = 10000000000000llu;

ull REC[1000100];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	REC[1] = 1;
	for (int n = 2; n <= 1'000'000; ++n)
	{
		REC[n] = REC[n - 1] * n;

		while (REC[n] % 10 == 0)
		{
			REC[n] /= 10;
		}

		REC[n] %= MOD;
	}

	int n;
	std::cin >> n;
	std::cout << std::setfill('0') << std::setw(5) << (REC[n] % 100'000);

	return 0;
}