#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
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

int P[10100];
int DP[2][10100];
bool VISITED[10100];
Edge* E[10100];
int N;

void dfs(int node)
{
	VISITED[node] = true;

	DP[0][node] = 0;
	DP[1][node] = P[node];
	for (const Edge* e = E[node]; e; e = e->next)
	{
		if (VISITED[e->v])
		{
			continue;
		}

		dfs(e->v);
		DP[0][node] += max(DP[0][e->v], DP[1][e->v]);
		DP[1][node] += DP[0][e->v];
	}
}

void cleanup()
{
	for (int i = 1; i <= N; ++i)
	{
		delete E[i];
		E[i] = nullptr;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);
	
	int N;
	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> P[i];
	}
	for (int i = 1; i < N; ++i)
	{
		int v1, v2;
		std::cin >> v1 >> v2;

		E[v1] = new Edge{ v2, E[v1] };
		E[v2] = new Edge{ v1, E[v2] };
	}

	dfs(1);

	std::cout << max(DP[0][1], DP[1][1]);

	cleanup();

	return 0;
}