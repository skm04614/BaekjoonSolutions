#include <cstdio>

constexpr auto MAX_SIZE = 1000;
constexpr auto INF = 0x7FFFFFFF;

inline int min(int n, int m)
{
	return n < m ? n : m;
}

inline int max(int n, int m)
{
	return n > m ? n : m;
}

template <typename T>
inline void swap(T& n, T& m)
{
	T x = n;
	n = m;
	m = x;
}

struct Element
{
	int id;
	int cost;

	bool operator>(const Element& other)
	{
		return cost < other.cost;
	}
};

struct Heap
{
	int n;
	Element values[10 * MAX_SIZE];

	Heap() : n{ 0 }, values{} {}

	bool is_empty()
	{
		return !n;
	}

	void push(int id, int cost)
	{
		values[++n] = {id, cost};
		
		int current = n;
		while (current > 1)
		{
			if (values[current / 2] > values[current])
			{
				break;
			}
			swap(values[current], values[current / 2]);
			current /= 2;
		}
	}

	Element pop()
	{
		Element ret = values[1];
		swap(values[n], values[1]);
		n--;

		int current = 1;
		while (2 * current <= n)
		{	
			int target = 2 * current;
			if (n >= target + 1 && values[target + 1] > values[target])
			{
				target++;
			}

			if (values[target] > values[current])
			{
				swap(values[current], values[target]);
				current = target;
				continue;
			}
			
			break;
		}
		return ret;
	}
};

int N;
int E;
int X;

int	W[MAX_SIZE + 1][MAX_SIZE + 1];
int MINCOST[MAX_SIZE + 1][MAX_SIZE + 1];


int dijkstra(int start, int dest)
{
	bool visited[MAX_SIZE + 1] = { 0, };
	
	Heap heap;

	heap.push(start, MINCOST[start][start]);
	while (!heap.is_empty())
	{
		Element curr = heap.pop();
		if (visited[curr.id])
		{
			continue;
		}
		visited[curr.id] = true;

		if (curr.id == dest)
		{
			return MINCOST[start][dest];
		}
		
		for (int adj = 1; adj <= N; adj++)
		{
			if (visited[adj] || W[curr.id][adj] == 0)
			{
				continue;
			}

			MINCOST[start][adj] = min(MINCOST[start][curr.id] + W[curr.id][adj], MINCOST[start][adj]);
			heap.push(adj, MINCOST[start][adj]);
		}


	}

	return INF;
}

int main(void)
{
	scanf("%d %d %d", &N, &E, &X);

	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			W[i][j] = 0;
			MINCOST[i][j] = INF;
		}
		MINCOST[i][i] = 0;
	}

	int i = 0, j = 0;
	for (int e = 0; e < E; e++)
	{
		scanf("%d %d", &i, &j);
		scanf("%d", &W[i][j]);
	}

	int sol = 0;
	for (int n = 1; n <= N; n++)
	{
		sol = max(sol, dijkstra(n, X) + dijkstra(X, n));
	}
	printf("%d", sol);

	return 0;
}