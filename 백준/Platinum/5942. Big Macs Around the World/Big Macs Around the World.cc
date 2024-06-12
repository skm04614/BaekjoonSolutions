#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

constexpr int MAX_N = 2010;
constexpr double INF = 3e14;

struct Edge
{
	int v0;
	int v1;
	double w;
	Edge* next;

	Edge(int v0, int v1, double w, Edge* next) : v0{ v0 }, v1{ v1 }, w{ w }, next{ next }
	{

	}

	~Edge()
	{
		delete next;
		next = nullptr;
	}
};

bool VISITED[MAX_N];
double COST[MAX_N];
Edge* EDGE_LIST;
int N;

void init()
{
	delete EDGE_LIST;
	EDGE_LIST = nullptr;

	for (int v = 0; v < MAX_N; ++v)
	{
		COST[v] = INF;
	}
}

void bellman_ford()
{
	for (const Edge* e = EDGE_LIST; e; e = e->next)
	{
		if (COST[e->v0] == INF)
		{
			continue;
		}

		const double cost = COST[e->v0] * e->w;
		if (COST[e->v1] > cost)
		{
			COST[e->v1] = cost;
		}
	}
}

bool is_reachable(int node, int dest)
{
	if (node == dest)
	{
		return true;
	}

	if (VISITED[node])
	{
		return false;
	}
	VISITED[node] = true;

	for (const Edge* e = EDGE_LIST; e; e = e->next)
	{
		if (is_reachable(e->v0, dest))
		{
			return true;
		}
	}

	return false;
}

bool has_inf_cycle(int dest)
{
	bool flag = false;
	for (const Edge* e = EDGE_LIST; e; e = e->next)
	{
		if (COST[e->v0] == INF)
		{
			continue;
		}

		const double cost = COST[e->v0] * e->w;
		if (COST[e->v1] > cost)
		{
			if (is_reachable(e->v1, dest))
			{
				return true;
			}
		}
	}

	return flag;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int M;
	double V;
	int A, B;
	std::cin >> N >> M >> V >> A >> B;

	init();

	for (int i = 0; i < M; ++i)
	{
		int v0, v1;
		double w;
		std::cin >> v0 >> v1 >> w;

		EDGE_LIST = new Edge{ v0, v1, w, EDGE_LIST };
	}

	COST[A] = V;

	for (int i = 0; i < N; ++i)
	{
		bellman_ford();
	}

	if (has_inf_cycle(B) || COST[B] == INF)
	{
		std::cout << 0;
	}
	else
	{
		std::cout << std::fixed << std::setprecision(6) << COST[B];
	}

	init();

	return 0;
}