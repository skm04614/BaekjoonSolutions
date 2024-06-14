#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int UNINITIALIZED = 0x7FFFFFFF;

int ARR[2020];
int DP[2020][2020];
int N;

int is_palindrome(int idx0, int idx1)
{
	if (idx0 > idx1)
	{
		return 1;
	}

	if (idx0 == idx1)
	{
		return DP[idx0][idx0] = 1;
	}

	if (DP[idx0][idx1] != UNINITIALIZED)
	{
		return DP[idx0][idx1];
	}

	return DP[idx0][idx1] = (is_palindrome(idx0 + 1, idx1 - 1) && (ARR[idx0] == ARR[idx1]));
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
		for (int j = 1; j <= N; ++j)
		{
			DP[i][j] = UNINITIALIZED;
		}
	}

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int left, right;
		std::cin >> left >> right;
		std::cout << is_palindrome(left, right) << '\n';
	}


	return 0;
}