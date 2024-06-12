#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

constexpr ll MOD = 1000000000;
constexpr ll ZERO_BASE = 1000000;

ll DP[2000001];

inline ll _abs(ll x)
{
	return x < 0 ? -x : x;
}

void fill_dp()
{
	DP[ZERO_BASE] = 0;
	DP[ZERO_BASE + 1] = 1;

	for (int n = 2; n <= 1000000; ++n)
	{
		DP[ZERO_BASE + n] = (DP[ZERO_BASE + n - 1] + DP[ZERO_BASE + n - 2]) % MOD;
	}

	for (int n = -1; n >= -1000000; --n)
	{
		DP[ZERO_BASE + n] = (DP[ZERO_BASE + n + 2] - DP[ZERO_BASE + n + 1]) % MOD;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	fill_dp();

	int n;
	std::cin >> n;
	ll val = DP[ZERO_BASE + n];
	std::cout << (val == 0 ? 0 : val / _abs(val)) << '\n';
	std::cout << _abs(val);

	return 0;
}