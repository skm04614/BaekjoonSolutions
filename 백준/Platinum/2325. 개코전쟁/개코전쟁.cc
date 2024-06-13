#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Adj
{
	int v;
	int w;
	Adj* next;

	Adj(int v, int w, Adj* next) : v{ v }, w{ w }, next { next }
	{

	}

	~Adj()
	{
		delete next;
		next = nullptr;
	}
};

struct Element
{
	int v;
	int cost;

	bool operator<=(const Element& other) const
	{
		return cost <= other.cost;
	}
};

struct Heap
{
	Element data[1010];
	int size;

	bool empty() const
	{
		return size == 0;
	}

	void push(Element e)
	{
		data[++size] = e;

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
		swap(data[1], data[size--]);

		int p = 1;
		int c = p << 1;
		while (c <= size)
		{
			if ((c | 1) <= size && data[c | 1] <= data[c])
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

		return data[size + 1];
	}
} HQ;

Adj* ADJ[1010];
int COST[1010];
int ORIGIN[1010];
int N;

void init()
{
	COST[1] = 0;
	for (int v = 2; v <= N; ++v)
	{
		COST[v] = INF;
	}
}

int dijkstra(int u, int w, int* origin = nullptr)
{
	init();

	HQ.push({ 1, 0 });
	while (!HQ.empty())
	{
		const Element& c = HQ.pop();
		if (COST[c.v] < c.cost)
		{
			continue;
		}

		for (const Adj* adj = ADJ[c.v]; adj; adj = adj->next)
		{
			if ((c.v == u && adj->v == w) || (c.v == w && adj->v == u))
			{
				continue;
			}

			const int new_cost = c.cost + adj->w;
			if (COST[adj->v] <= new_cost)
			{
				continue;
			}

			if (origin)
			{
				origin[adj->v] = c.v;
			}

			COST[adj->v] = new_cost;
			HQ.push({ adj->v, new_cost });
		}
	}

	return COST[N];
}

void cleanup()
{
	for (int i = 1; i <= N; ++i)
	{
		delete ADJ[i];
		ADJ[i] = nullptr;
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
		int u, v, w;
		std::cin >> u >> v >> w;

		ADJ[u] = new Adj{ v, w, ADJ[u] };
		ADJ[v] = new Adj{ u, w, ADJ[v] };
	}

	int res = dijkstra(0, 0, ORIGIN);
	for (int v = N; v != 1; v = ORIGIN[v])
	{
		int tmp = dijkstra(ORIGIN[v], v);
		if (tmp == INF)
		{
			continue;
		}

		res = max(res, tmp);
	}
	std::cout << res;

	cleanup();

	return 0;
}