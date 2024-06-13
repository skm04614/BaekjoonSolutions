#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int ARR[2020];
int N;

int DP[2020][2020];

int fill_dp(int idx0, int idx1, int depth)
{
	if (idx0 == idx1)
	{
		return DP[idx0][idx0] = depth * ARR[idx0];
	}

	if (DP[idx0][idx1])
	{
		return DP[idx0][idx1];
	}

	return DP[idx0][idx1] = max(fill_dp(idx0 + 1, idx1, depth + 1) + depth * ARR[idx0], fill_dp(idx0, idx1 - 1, depth + 1) + depth * ARR[idx1]);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> ARR[i];
	}

	std::cout << fill_dp(1, N, 1);

	return 0;
}