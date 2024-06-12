#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& n, T& m)
{
	T tmp = n;
	n = m;
	m = tmp;
}

struct Edge
{
	int dest;
	Edge* next;
};

Edge POOL[100100];
int M;

int IN_DEGREES[33000];
Edge* EDGES[33000];
int N;

bool is_less(int v1, int v2)
{
	if (IN_DEGREES[v1] == IN_DEGREES[v2])
	{
		return v1 <= v2;
	}

	return IN_DEGREES[v1] < IN_DEGREES[v2];
}

struct MinHeap
{
	int idx[33000];
	int size;

	bool empty() const
	{
		return size == 0;
	}

	void push(int v)
	{
		idx[++size] = v;

		register int c = size;
		while (c > 1)
		{
			register int p = c >> 1;
			if (is_less(idx[p], idx[c]))
			{
				break;
			}

			swap(idx[c], idx[p]);
			c = p;
		}
	}

	int pop()
	{
		int ret = idx[1];
		swap(idx[1], idx[size--]);

		register int p = 1;
		register int c = p << 1;
		while (c <= size)
		{
			if ((c | 1) <= size && is_less(idx[c | 1], idx[c]))
			{
				c |= 1;
			}

			if (is_less(idx[p], idx[c]))
			{
				break;
			}

			swap(idx[c], idx[p]);
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
	for (register int i = 1; i <= M; i++)
	{
		Edge& edge = POOL[i];

		register int src;
		std::cin >> src >> edge.dest;

		++IN_DEGREES[edge.dest];

		edge.next = EDGES[src];
		EDGES[src] = &edge;
	}

	for (register int v = 1; v <= N; v++)
	{
		if (IN_DEGREES[v] == 0)
		{
			HQ.push(v);
		}
	}

	while (!HQ.empty())
	{
		const int v0 = HQ.pop();
		std::cout << v0 << ' ';

		for (register Edge* edge = EDGES[v0]; edge; edge = edge->next)
		{
			register const int v1 = edge->dest;

			if (--IN_DEGREES[v1] == 0)
			{
				HQ.push(v1);
			}
		}
	}

	return 0;
}