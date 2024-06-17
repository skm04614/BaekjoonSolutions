#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int DP[2020][2020];
int L[2020];
int R[2020];
int N;

int fill_dp(int l, int r)
{
	if (l == N || r == N)
	{
		return DP[l][r];
	}

	if (DP[l][r])
	{
		return DP[l][r];
	}

	if (R[r] < L[l])
	{
		DP[l][r] = max(DP[l][r], fill_dp(l, r + 1) + R[r]);
	}

	DP[l][r] = max(DP[l][r], fill_dp(l + 1, r + 1));
	DP[l][r] = max(DP[l][r], fill_dp(l + 1, r));

	return DP[l][r];
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 0; i < N; ++i)
	{
		std::cin >> L[i];
	}
	for (int i = 0; i < N; ++i)
	{
		std::cin >> R[i];
	}

	std::cout << fill_dp(0, 0);

	return 0;
}