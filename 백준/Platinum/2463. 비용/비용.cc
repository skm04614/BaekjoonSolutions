#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
	int v1;
	int v2;
	int w;

	bool operator<=(const Edge& other)
	{
		return w <= other.w;
	}
};

Edge EDGES[100100];
int M;

template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

void __heapify(Edge* arr, int size)
{
	for (int s = 1; s <= size; s++)
	{
		int c = s;
		while (c > 1)
		{
			int p = c >> 1;
			if (arr[p] <= arr[c])
			{
				break;
			}

			swap(arr[p], arr[c]);
			c = p;
		}
	}
}

void sort(Edge* arr, int size)
{
	__heapify(arr, size);
	for (int s = size; s >= 1; s--)
	{
		swap(arr[1], arr[s]);

		const int max_s = s - 1;
		int p = 1;
		int c = p << 1;
		while (c <= max_s)
		{
			if ((c | 1) <= max_s && arr[c | 1] <= arr[c])
			{
				c |= 1;
			}

			if (arr[p] <= arr[c])
			{
				break;
			}

			swap(arr[p], arr[c]);
			p = c;
			c = p << 1;
		}
	}

}

int PARENT[100100];
unsigned long long SIZE[100100];
int N;

void init(void)
{
	for (int i = 1; i <= N; i++)
	{
		PARENT[i] = i;
		SIZE[i] = 1;
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
		SIZE[v1] += SIZE[v2];
		SIZE[v2] = 0;
	}
	else if (v2 < v1)
	{
		PARENT[v1] = v2;
		SIZE[v2] += SIZE[v1];
		SIZE[v1] = 0;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;

	init();

	unsigned long long total_w = 0;
	for (int i = 1; i <= M; i++)
	{
		Edge& edge = EDGES[i];
		std::cin >> edge.v1 >> edge.v2 >> edge.w;
		total_w += edge.w;
	}

	sort(EDGES, M);

	unsigned long long sol = 0;
	for (int i = 1; i <= M; i++)
	{
		Edge& edge = EDGES[i];

		int v1 = find(edge.v1);
		int v2 = find(edge.v2);

		if (v1 != v2)
		{
			sol = (sol + (SIZE[v1] * SIZE[v2] * total_w)) % 1000000000;
			_union(v1, v2);
		}

		total_w -= edge.w;
	}
	std::cout << sol;

	return 0;
}