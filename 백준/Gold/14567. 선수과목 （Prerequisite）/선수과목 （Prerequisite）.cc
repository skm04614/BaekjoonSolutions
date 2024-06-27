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

Edge* E[100100];
int IN_DEGREES[100100];
int COST[100100];
int N;

int Q[100100];
int LP;
int RP;

void init()
{
	for (int i = 1; i <= N; ++i)
	{
		if (IN_DEGREES[i] == 0)
		{
			Q[++RP] = i;
		}

		COST[i] = 1;
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

	int M;
	std::cin >> N >> M;
	for (int i = 1; i <= M; ++i)
	{
		int v1, v2;
		std::cin >> v1 >> v2;

		E[v1] = new Edge{ v2, E[v1] };
		++IN_DEGREES[v2];
	}

	init();
	while (RP > LP)
	{
		const int v = Q[++LP];
		
		for (const Edge* e = E[v]; e; e = e->next)
		{
			COST[e->v] = max(COST[e->v], COST[v] + 1);

			if (--IN_DEGREES[e->v] == 0)
			{
				Q[++RP] = e->v;
			}
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		std::cout << COST[i] << ' ';
	}

	cleanup();
	return 0;
}