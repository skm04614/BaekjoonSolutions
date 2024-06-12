#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int CARDS[100010];
int N, M;
int ANS;

void sol(int depth, int sidx, int sum)
{
	if (sum > M)
	{
		return;
	}

	if (depth == 3)
	{
		ANS = ANS > sum ? ANS : sum;
		return;
	}

	for (int i = sidx; i < N; i++)
	{
		sol(depth + 1, i + 1, sum + CARDS[i]);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;

	for (int i = 0; i < N; i++)
	{
		std::cin >> CARDS[i];
	}

	sol(0, 0, 0);

	std::cout << ANS;

	return 0;
}