#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
	return x < y ? x : y;
}

struct Edge
{
	int v;
	int w;
	Edge* next;

	Edge(int v, int w, Edge* next) : v{ v }, w{ w }, next{ next }
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
int DP[100100];
int N;

void cleanup()
{
	for (int i = 1; i <= N; ++i)
	{
		delete E[i];
		E[i] = nullptr;
	}
}

int sol(int node, int w)
{
	DP[node] = w;
	int sum = 0;
	for (const Edge* e = E[node]; e; e = e->next)
	{
		if (VISITED[e->v])
		{
			continue;
		}
		VISITED[e->v] = true;

		sum += sol(e->v, e->w);
	}

	if (sum)
	{
		DP[node] = min(DP[node], sum);
	}

	return DP[node];
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i < N; ++i)
	{
		int v1, v2, w;
		std::cin >> v1 >> v2 >> w;

		E[v1] = new Edge{ v2, w, E[v1] };
		E[v2] = new Edge{ v1, w, E[v2] };
	}
	VISITED[1] = true;
	int res = sol(1, 0x7FFFFFFF);
	std::cout << (res == 0x7FFFFFFF ? 0 : res);

	cleanup();
	return 0;
}