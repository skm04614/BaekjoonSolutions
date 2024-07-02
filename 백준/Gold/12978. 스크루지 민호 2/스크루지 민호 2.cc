#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
	return x < y ? x : y;
}

struct Edge
{
	int v;
	Edge* next;

	Edge(int v, Edge* next) : v{ v }, next{ next }
	{

	}

	~Edge()
	{
		delete next;
		next = nullptr;
	}
};

Edge* E[100100];
bool VISITED[100100];
int DP[2][100100];
int N;

void sol(int node)
{
	VISITED[node] = true;

	DP[1][node] = 1;
	for (const Edge* e = E[node]; e; e = e->next)
	{
		if (VISITED[e->v])
		{
			continue;
		}

		sol(e->v);
		DP[0][node] += DP[1][e->v];
		DP[1][node] += min(DP[0][e->v], DP[1][e->v]);
	}
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 0; i < N - 1; ++i)
	{
		int v1, v2;
		std::cin >> v1 >> v2;

		E[v1] = new Edge{ v2, E[v1] };
		E[v2] = new Edge{ v1, E[v2] };
	}

	sol(1);
	std::cout << min(DP[0][1], DP[1][1]);

	return 0;
}
