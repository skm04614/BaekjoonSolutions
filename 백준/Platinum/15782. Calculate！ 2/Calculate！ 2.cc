#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
	int dest;
	Edge* next;
};

struct EulerNode
{
	int start;
	int end;
};

Edge POOL[200200];
Edge* EDGES[100100];

bool VISITED[100100];

EulerNode EN[100100];
int E;

void dfs_fill_EN(int node)
{
	++E;
	EN[node].start = E;
	VISITED[node] = true;

	for (const Edge* edge = EDGES[node]; edge; edge = edge->next)
	{
		if (VISITED[edge->dest])
		{
			continue;
		}

		dfs_fill_EN(edge->dest);
	}

	EN[node].end = E;
}

int ARR[100100];
int SEG_TREE[400400];
int LAZY[400400];
int N;

void init(int node, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		SEG_TREE[node] = ARR[idx0];
		return;
	}

	int mid = (idx0 + idx1) >> 1;
	init(node << 1, idx0, mid);
	init(node << 1 | 1, mid + 1, idx1);

	SEG_TREE[node] = SEG_TREE[node << 1] ^ SEG_TREE[node << 1 | 1];
}

void propagate(int node, int idx0, int idx1)
{
	if (LAZY[node])
	{
		if ((idx1 - idx0 + 1) % 2)
		{
			SEG_TREE[node] ^= LAZY[node];
		}

		if (idx0 != idx1)
		{
			LAZY[node << 1] ^= LAZY[node];
			LAZY[node << 1 | 1] ^= LAZY[node];
		}

		LAZY[node] = 0;
	}
}

void update(int node, int idx0, int idx1, int left, int right, int k)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return;
	}

	if (left <= idx0 && idx1 <= right)
	{
		LAZY[node] = k;
		propagate(node, idx0, idx1);
		return;
	}

	int mid = (idx0 + idx1) >> 1;
	update(node << 1, idx0, mid, left, right, k);
	update(node << 1 | 1, mid + 1, idx1, left, right, k);

	SEG_TREE[node] = SEG_TREE[node << 1] ^ SEG_TREE[node << 1 | 1];
}

int query(int node, int idx0, int idx1, int left, int right)
{
	propagate(node, idx0, idx1);

	if (idx1 < left || right < idx0)
	{
		return 0;
	}

	if (left <= idx0 && idx1 <= right)
	{
		return SEG_TREE[node];
	}

	int mid = (idx0 + idx1) >> 1;
	return query(node << 1, idx0, mid, left, right) ^ query(node << 1 | 1, mid + 1, idx1, left, right);
}


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int M;
	std::cin >> N >> M;
	for (register int i = 1; i < N; i++)
	{
		Edge& edge_1 = POOL[2 * i];
		Edge& edge_2 = POOL[2 * i + 1];

		register int src, dest;
		std::cin >> src >> dest;

		edge_1.next = EDGES[src];
		edge_1.dest = dest;
		EDGES[src] = &edge_1;

		edge_2.next = EDGES[dest];
		edge_2.dest = src;
		EDGES[dest] = &edge_2;
	}

	dfs_fill_EN(1);

	for (register int i = 1; i <= N; i++)
	{
		std::cin >> ARR[EN[i].start];
	}

	init(1, 1, N);

	while (M--)
	{
		int a, b;
		std::cin >> a >> b;
		if (a == 1)
		{
			std::cout << query(1, 1, N, EN[b].start, EN[b].end) << '\n';
		}
		else
		{
			int c;
			std::cin >> c;
			update(1, 1, N, EN[b].start, EN[b].end, c);
		}
	}

	return 0;
}