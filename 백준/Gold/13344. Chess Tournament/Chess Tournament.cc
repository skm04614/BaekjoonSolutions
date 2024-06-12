#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct RawEdge
{
	int src;
	int dest;
};

RawEdge RAW_EDGE[250250];
int M;

struct Edge
{
	int v_dest;
	Edge* next;
};

Edge POOL[250250];

Edge* EDGES[50050];
int PARENT[50050];
int IN_DEGREE[50050];
int N;

void init()
{
	for (int v = 0; v < N; v++)
	{
		PARENT[v] = v;
	}
}

int find(int v)
{
	if (PARENT[v] == v)
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
	}
	else
	{
		PARENT[v1] = v2;
	}
}

int Q[50050];
int LP;
int RP;

void sol(void)
{
	LP = -1;
	RP = -1;

	for (int i = 0; i < M; i++)
	{
		int src = find(RAW_EDGE[i].src);
		int dest = find(RAW_EDGE[i].dest);
		if (src == dest)
		{
			std::cout << "inconsistent";
			return;
		}

		++IN_DEGREE[dest];

		Edge& edge = POOL[i];
		edge.v_dest = dest;
		edge.next = EDGES[src];
		EDGES[src] = &edge;
	}

	for (int v = 0; v < N; v++)
	{
		if (IN_DEGREE[v])
		{
			continue;
		}
		Q[++RP] = v;
	}

	while (RP > LP)
	{
		int src = Q[++LP];

		for (const Edge* edge = EDGES[src]; edge; edge = edge->next)
		{
			if (--IN_DEGREE[edge->v_dest])
			{
				continue;
			}

			Q[++RP] = edge->v_dest;
		}
	}

	for (int v = 0; v < N; v++)
	{
		if (IN_DEGREE[v])
		{
			std::cout << "inconsistent";
			return;
		}
	}

	std::cout << "consistent";
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int m;
	std::cin >> N >> m;

	init();

	for (int i = 0; i < m; i++)
	{
		int p1, p2;
		char op;
		std::cin >> p1 >> op >> p2;
		switch (op)
		{
		case '=':
			_union(p1, p2);
			break;
		case '<':
			RAW_EDGE[M++] = { p1, p2 };
			break;
		default:
			RAW_EDGE[M++] = { p2, p1 };
			break;
		}
	}

	sol();

	return 0;
}