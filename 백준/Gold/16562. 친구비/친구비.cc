#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[10100];
int COST[10100];
int N;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

int find(int v)
{
	if (v == PARENT[v])
	{
		return v;
	}

	return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

	if (v1 < v2)
	{
		PARENT[v2] = v1;
		COST[v1] = min(COST[v1], COST[v2]);
	}
	else
	{
		PARENT[v1] = v2;
		COST[v2] = min(COST[v2], COST[v1]);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int M, BUDGET;
	std::cin >> N >> M >> BUDGET;
	for (register int v = 1; v <= N; v++)
	{
		PARENT[v] = v;
		std::cin >> COST[v];
	}

	for (register int i = 0; i < M; i++)
	{
		register int src, dest;
		std::cin >> src >> dest;

		_union(src, dest);
	}

	int net_cost = 0;
	for (register int v = 1; v <= N; v++)
	{
		net_cost += (v == find(v)) * COST[v];
	}
	
	if (BUDGET >= net_cost)
	{
		std::cout << net_cost;
	}
	else
	{
		std::cout << "Oh no";
	}


	return 0;
}