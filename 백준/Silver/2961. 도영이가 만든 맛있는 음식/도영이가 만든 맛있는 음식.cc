#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int FOOD[2][10];
int N;
int SOL = 0x7FFFFFFF;

int abs(int x)
{
	return x < 0 ? -x : x;
}

void sol(int sidx, int sour, int bitter)
{
	if (sidx == N && bitter != 0)
	{
		int res = abs(sour - bitter);
		SOL = SOL < res ? SOL : res;
		return;
	}

	for (int i = sidx; i < N; i++)
	{
		sol(i + 1, sour, bitter);
		sol(i + 1, sour * FOOD[0][i], bitter + FOOD[1][i]);
	}
	
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> FOOD[0][i] >> FOOD[1][i];
		int result = abs(FOOD[0][i] - FOOD[1][i]);
		SOL = SOL < result ? SOL : result;
	}
	sol(0, 1, 0);
	std::cout << SOL;
	
	return 0;
}