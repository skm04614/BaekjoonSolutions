#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int N, M;
int SOL[10];

void sol(int depth)
{
	if (depth == M)
	{
		for (int i = 0; i < depth; i++)
		{
			std::cout << SOL[i] << ' ';
		}
		std::cout << '\n';
		return;
	}

	for (int i = 0; i < N; i++)
	{
		SOL[depth] = i + 1;
		sol(depth + 1);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	std::cin >> N >> M;

	sol(0);

	return 0;
}