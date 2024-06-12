#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x2FFFFFFFFFFFFFFF;

inline ull min(ull x, ull y)
{
	return x < y ? x : y;
}

template <typename T>
void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

struct Edge
{
	int v;
	ull w;
	Edge* next;

	Edge(int v, ull w, Edge* next) : v{ v }, w{ w }, next{ next }
	{

	}

	~Edge()
	{
		delete next;
		next = nullptr;
	}
};

Edge* EDGES[100100];
ull COST_1[100100];
ull COST_2[100100];
int N;

int SRC, DEST;
int XMID[100100];
int K;

void cleanup()
{
	for (int v = 1; v <= N; ++v)
	{
		delete EDGES[v];
		EDGES[v] = nullptr;
	}
}

void init()
{
	for (int v = 1; v <= N; ++v)
	{
		COST_1[v] = COST_2[v] = INF;
	}
}

struct Element
{
	int v;
	ull cost;

	bool operator<=(const Element& other) const
	{
		return cost <= other.cost;
	}
};

struct Heap
{
	Element data[100100];
	int _size;

	bool empty() const
	{
		return _size == 0;
	}

	void push(Element e)
	{
		data[++_size] = e;

		int c = _size;
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
		swap(data[1], data[_size--]);

		int p = 1;
		int c = p << 1;
		while (c <= _size)
		{
			if ((c | 1) <= _size && data[c | 1] <= data[c])
			{
				c |= 1;
			}

			if (data[p] <= data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			p = c;
			c = p << 1;
		}

		return data[_size + 1];
	}
} HQ;

void dijkstra(int src, ull* cost)
{
	cost[src] = 0;
	HQ.push({ src, cost[src] });

	while (!HQ.empty())
	{
		const Element& c = HQ.pop();
		if (cost[c.v] < c.cost)
		{
			continue;
		}

		for (const Edge* e = EDGES[c.v]; e; e = e->next)
		{
			if (cost[e->v] <= cost[c.v] + e->w)
			{
				continue;
			}

			cost[e->v] = cost[c.v] + e->w;
			HQ.push({ e->v, cost[e->v] });
		}
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
		int u, v;
		ull w;
		std::cin >> u >> v >> w;

		EDGES[v] = new Edge{ u, w, EDGES[v] };
		EDGES[u] = new Edge{ v, w, EDGES[u] };
	}

	std::cin >> SRC >> DEST;
	std::cin >> K;
	for (int i = 1; i <= K; ++i)
	{
		std::cin >> XMID[i];
	}

	init();
	dijkstra(SRC, COST_1);
	dijkstra(DEST, COST_2);

	ull cost = INF;
	for (int i = 1; i <= K; ++i)
	{
		cost = min(cost, COST_1[XMID[i]] + COST_2[XMID[i]]);
	}

	if (cost == INF)
	{
		std::cout << -1;
	}
	else
	{
		std::cout << cost;
	}

	cleanup();

	return 0;
}