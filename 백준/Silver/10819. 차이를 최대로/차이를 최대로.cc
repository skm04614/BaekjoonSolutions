#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int N;
int ARR[8];
bool VISITED[8];
int SOL;


inline int abs(int x)
{
	return x < 0 ? -x : x;
}

void sol(int depth, int last_val, int sum)
{
	if (depth == N)
	{
		SOL = SOL > sum ? SOL : sum;
		return;
	}

	for (int i = 0; i < N; i++)
	{
		if (VISITED[i])
		{
			continue;
		}
		VISITED[i] = true;
		sol(depth + 1, ARR[i], depth == 0 ? 0 : sum + abs(last_val - ARR[i]));
		VISITED[i] = false;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int n = 0; n < N; n++)
	{
		std::cin >> ARR[n];
	}
	sol(0, 0, 0);
	std::cout << SOL;
	
	return 0;
}