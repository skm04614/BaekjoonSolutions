#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[10010];
int VISITED[10010];
int N;

int Q[10010];
int LP;
int RP;

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

	int S, E;
	std::cin >> S >> E;

	Q[++RP] = S;
	VISITED[S] = 1;

	while (RP > LP)
	{
		const int c = Q[++LP];
		const int step = ARR[c];

		const int l = (1 - c) / step - 1;
		const int r = (N - c) / step + 1;

		for (int i = l; i <= r; ++i)
		{
			const int n = c + i * step;

			if (n <= 0 || n > N || VISITED[n])
			{
				continue;
			}

			VISITED[n] = VISITED[c] + 1;
			Q[++RP] = n;
		}
	}

	if (VISITED[E])
	{
		std::cout << VISITED[E] - 1;
	}
	else
	{
		std::cout << -1;
	}

	return 0;
}