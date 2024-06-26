#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

int E[1 << 22];
int DP_MAX[1 << 22];
int N;

int sol(int node)
{
	if (node > N)
	{
		return 0;
	}

	int left = sol(node << 1);
	int right = sol(node << 1 | 1);


	DP_MAX[node] = max(E[node << 1] + DP_MAX[node << 1],
		               E[node << 1 | 1] + DP_MAX[node << 1 | 1]);

	return left + right + ((DP_MAX[node] << 1) - DP_MAX[node << 1] - DP_MAX[node << 1 | 1]);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	N = (1 << (N + 1));
	for (int i = 2; i < N; ++i)
	{
		std::cin >> E[i];
	}

	std::cout << sol(1);

	return 0;
}