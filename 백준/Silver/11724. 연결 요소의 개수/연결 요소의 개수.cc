#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int MAP[1010][1010];
bool VISITED[1010];
int N;
int M;

int sol(int src)
{
	if (VISITED[src])
	{
		return 0;
	}
	VISITED[src] = true;

	int result = 1;
	for (int dest = 1; dest <= N; dest++)
	{
		if (MAP[src][dest])
		{
			result += sol(dest);
		}
	}

	return result;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int s, d;
		std::cin >> s >> d;
		MAP[s][d] = MAP[d][s] = 1;
	}

	int result = 0;
	for (int src = 1; src <= N; src++)
	{
		result += (sol(src) > 0);

	}
	std::cout << result;

	return 0;
}