#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

struct Element
{
	int v;
	int cost;

	bool operator<(const Element& other) const
	{
		return cost < other.cost;
	}
};

inline void swap(Element& e1, Element& e2)
{
	Element tmp = e1;
	e1 = e2;
	e2 = tmp;
}

struct MinHeap
{
	Element data[100100];
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
			if (data[p] < data[c])
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
		while ((p << 1) <= size)
		{
			int c = p << 1;
			if (c + 1 <= size && data[c + 1] < data[c])
			{
				c = c + 1;
			}

			if (data[p] < data[c])
			{
				break;
			}

			swap(data[p], data[c]);
			p = c;
		}

		return ret;
	}

	void clear()
	{
		size = 0;
	}
};

MinHeap HQ;

struct Adj
{
	int dest;
	int w;
	Adj* next;

	Adj(int dest, int w, Adj* next) : dest{ dest }, w{ w }, next { next }
	{

	}

	~Adj()
	{
		if (next)
		{
			delete next;
			next = nullptr;
		}
	}
};

Adj* ADJ[10010];
int COST[10010];

void sol()
{
	int n, d, c;
	std::cin >> n >> d >> c;
	for (int i = 1; i <= n; i++)
	{
		COST[i] = INF;
	}

	for (int i = 1; i <= d; i++)
	{
		int a, b, c;
		std::cin >> a >> b >> c;

		ADJ[b] = new Adj{ a, c, ADJ[b] };
	}

	COST[c] = 0;
	HQ.push({ c, COST[c]});

	while (!HQ.empty())
	{
		const Element current = HQ.pop();
		if (current.cost > COST[current.v])
		{
			continue;
		}

		for (Adj* adj = ADJ[current.v]; adj; adj = adj->next)
		{
			if (COST[current.v] + adj->w < COST[adj->dest])
			{
				COST[adj->dest] = COST[current.v] + adj->w;
				HQ.push({ adj->dest, COST[adj->dest] });
			}
		}
	}

	int count = 0;
	int max = 0;
	for (int i = 1; i <= n; i++)
	{
		if (COST[i] < INF)
		{
			count++;
			max = max > COST[i] ? max : COST[i];
		}

		if (ADJ[i])
		{
			delete ADJ[i];
			ADJ[i] = nullptr;
		}
	}

	HQ.clear();

	std::cout << count << ' ' << max << '\n';
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int T;
	std::cin >> T;
	while (T--)
	{
		sol();
	}
	return 0;
}