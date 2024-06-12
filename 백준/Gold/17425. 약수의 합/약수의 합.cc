#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

int F[1000100];
ull G[1000100];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	for (int n = 1; n <= 1000000; ++n)
	{
		for (int c = 1; n * c <= 1000000; ++c)
		{
			F[n * c] += n;
		}
	}

	for (int n = 1; n <= 1000000; ++n)
	{
		G[n] = G[n - 1] + F[n];
	}

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		int v;
		std::cin >> v;
		std::cout << G[v] << '\n';
	}


	return 0;
}