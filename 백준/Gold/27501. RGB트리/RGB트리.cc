#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

const char COLORS[4] = "RGB";

enum
{
	R = 0,
	G = 1,
	B = 2,
	X = 3
};

using ull = unsigned long long;

inline ull max(ull x, ull y)
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

Edge* E[500500];
bool VISITED[500500];
ull C[3][500500];
ull DP[3][500500];
char REC[500500];
int N;

void sol(int node)
{
	VISITED[node] = true;

	DP[R][node] = C[R][node];
	DP[G][node] = C[G][node];
	DP[B][node] = C[B][node];
	for (const Edge* e = E[node]; e; e = e->next)
	{
		if (VISITED[e->v])
		{
			continue;
		}

		sol(e->v);

		DP[R][node] += max(DP[G][e->v], DP[B][e->v]);
		DP[G][node] += max(DP[B][e->v], DP[R][e->v]);
		DP[B][node] += max(DP[R][e->v], DP[G][e->v]);
	}
}

void traverse(int node, int exclude)
{
	VISITED[node] = false;

	ull maximum = 0;
	int color = 0;
	for (int c = 0; c < 3; ++c)
	{
		if (c == exclude)
		{
			continue;
		}

		if (DP[c][node] > maximum)
		{
			maximum = DP[c][node];
			color = c;
		}
	}

	REC[node] = COLORS[color];

	for (const Edge* e = E[node]; e; e = e->next)
	{
		if (VISITED[e->v] == false)
		{
			continue;
		}

		traverse(e->v, color);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i < N; ++i)
	{
		int v1, v2;
		std::cin >> v1 >> v2;

		E[v1] = new Edge{ v2, E[v1] };
		E[v2] = new Edge{ v1, E[v2] };
	}
	for (int i = 1; i <= N; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			std::cin >> C[j][i];
		}
	}

	sol(1);

	ull res = max(max(DP[R][1], DP[G][1]), DP[B][1]);
	std::cout << res << '\n';

	traverse(1, X);
	std::cout << (REC + 1);

	return 0;
}