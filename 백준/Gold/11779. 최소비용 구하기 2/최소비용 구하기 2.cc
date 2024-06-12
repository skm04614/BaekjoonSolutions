#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x7FFFFFFFFFFFFFFF;

struct Edge
{
	int dest;
	int w;
	Edge* next;
};

Edge POOL[100100];
int M;

Edge* EDGES[1010];
ull COST[1010];
int RECORD[1010];
int N;

void print_record(int node, int depth)
{
	if (node == 0)
	{
		std::cout << depth << '\n';
		return;
	}

	print_record(RECORD[node], depth + 1);
	std::cout << node << ' ';
}

struct Element
{
	int v;
	ull cost;

	bool operator<=(const Element & other) const
	{
		return cost <= other.cost;
	}
};

inline void swap(Element &e1, Element &e2)
{
	Element tmp = e1;
	e1 = e2;
	e2 = tmp;
}

struct MinHeap
{
	Element data[10100];
	int size;

	bool empty() const
	{
		return size == 0;
	}

	void push(int v, ull cost)
	{
		data[++size] = { v, cost };

		int c = size;
		while (c > 1)
		{
			int p = c >> 1;
			if (data[p] <= data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			c = p;
		}
	}

	Element pop()
	{
		Element ret = data[1];
		swap(data[1], data[size--]);

		int p = 1;
		int c = p << 1;
		while (c <= size)
		{
			if (c + 1 <= size && data[c + 1] <= data[c])
			{
				++c;
			}

			if (data[p] <= data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			p = c;
			c = p << 1;
		}

		return ret;
	}
} HQ;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int i = 0; i < M; i++)
	{
		int src;
		std::cin >> src >> POOL[i].dest >> POOL[i].w;

		POOL[i].next = EDGES[src];
		EDGES[src] = &POOL[i];
	}

	for (int i = 1; i <= N; i++)
	{
		COST[i] = INF;
	}

	int V0, V1;
	std::cin >> V0 >> V1;

	COST[V0] = 0;
	HQ.push(V0, COST[V0]);
	while (!HQ.empty())
	{
		const Element current = HQ.pop();
		if (current.cost > COST[current.v])
		{
			continue;
		}

		for (Edge* edge = EDGES[current.v]; edge; edge = edge->next)
		{
			if (COST[current.v] + edge->w >= COST[edge->dest])
			{
				continue;
			}

			COST[edge->dest] = COST[current.v] + edge->w;
			HQ.push(edge->dest, COST[edge->dest]);
			RECORD[edge->dest] = current.v;
		}
	}

	std::cout << COST[V1] << '\n';
	print_record(V1, 0);

	return 0;
}