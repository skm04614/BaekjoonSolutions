#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

struct Element
{
	int target;
	int w;
	Element* next;

	Element(int target, int w, Element* next) : target{ target }, w{ w }, next{ next }
	{

	}

	~Element()
	{
		if (next)
		{
			delete next;
			next = nullptr;
		}
	}
};

Element* EDGES[20010];
int COST[20010];
int V;
int E;

struct D
{
	int v;
	int cost;

	bool operator>=(const D& other) const
	{
		return cost >= other.cost;
	}
};

inline void swap(D& x, D& y)
{
	D tmp = x;
	x = y;
	y = tmp;
}

struct MinHeap
{
	D data[3000300];
	int size;

	void push(D d)
	{
		data[++size] = d;

		int c = size;
		while (c > 1)
		{
			if (data[c] >= data[c / 2])
			{
				break;
			}

			swap(data[c], data[c / 2]);
			c /= 2;
		}
	}

	D pop()
	{
		D ret = data[1];
		swap(data[1], data[size--]);

		int p = 1;
		while (2 * p <= size)
		{
			int c1 = 2 * p;
			int c2 = c1 + 1;
			int c = c1;
			
			if (c2 <= size && data[c1] >= data[c2])
			{
				c = c2;
			}

			if (data[c] >= data[p])
			{
				break;
			}

			swap(data[p], data[c]);
			p = c;
		}

		return ret;
	}

	bool empty() const
	{
		return size == 0;
	}

} MH;


int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> V >> E;
	for (int v = 1; v <= V; v++)
	{
		COST[v] = INF;
	}
	
	int v0;
	std::cin >> v0;
	
	for (int i = 0; i < E; i++)
	{
		int v1, v2, w;
		std::cin >> v1 >> v2 >> w;

		EDGES[v1] = new Element{ v2, w, EDGES[v1] };
	}

	MH.push({ v0, 0 });
	COST[v0] = 0;

	while (!MH.empty())
	{
		const D& d = MH.pop();
		if (d.cost > COST[d.v])
		{
			continue;
		}

		for (Element* e = EDGES[d.v]; e; e = e->next)
		{
			int c = d.cost + e->w;
			if (COST[e->target] > c)
			{
				COST[e->target] = c;
				MH.push({ e->target, c });
			}
		}
	}

	for (int v = 1; v <= V; v++)
	{
		if (COST[v] == INF)
		{
			std::cout << "INF\n";
		}
		else
		{
			std::cout << COST[v] << '\n';
		}
	}

	for (int v = 1; v <= V; v++)
	{
		if (EDGES[v])
		{
			delete EDGES[v];
		}
	}

	return 0;
}