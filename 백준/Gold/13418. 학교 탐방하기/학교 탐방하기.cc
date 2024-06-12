#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
void sort(T* arr, int size)
{
	for (int s = 1; s <= size; ++s)
	{
		int c = s;
		while (c > 1)
		{
			int p = c >> 1;
			if (arr[p] >= arr[c])
			{
				break;
			}

			swap(arr[p], arr[c]);
			c = p;
		}
	}

	for (int s = size; s >= 1; --s)
	{
		swap(arr[1], arr[s]);
		const int max_s = s - 1;

		int p = 1;
		int c = p << 1;
		while (c <= max_s)
		{
			if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
			{
				c |= 1;
			}

			if (arr[p] >= arr[c])
			{
				break;
			}

			swap(arr[p], arr[c]);
			p = c;
			c = p << 1;
		}
	}
}

int PARENT[1010];
int N;

void init()
{
	for (int v = 0; v <= N; ++v)
	{
		PARENT[v] = v;
	}
}

int find(int v)
{
	if (v == PARENT[v])
	{
		return v;
	}

	return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

	if (v1 == v2)
	{
		return;
	}

	if (v1 < v2)
	{
		PARENT[v2] = v1;
	}
	else
	{
		PARENT[v1] = v2;
	}
}

struct Edge
{
	int v1;
	int v2;
	int w;

	bool operator>=(const Edge& other) const
	{
		return w >= other.w;
	}
};

Edge EDGES[1001000];
int M;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N >> M;

	++M;
	for (int i = 1; i <= M; ++i)
	{
		Edge& e = EDGES[i];
		std::cin >> e.v1 >> e.v2 >> e.w;
		e.w ^= 1;
	}

	sort(EDGES, M);

	init();
	unsigned long long min = 0;
	for (int i = 1;i <= M; ++i)
	{
		const Edge& e = EDGES[i];

		if (find(e.v1) == find(e.v2))
		{
			continue;
		}

		_union(e.v1, e.v2);
		min += e.w;
	}

	init();
	unsigned long long max = 0;
	for (int i = M;i >= 1; --i)
	{
		const Edge& e = EDGES[i];

		if (find(e.v1) == find(e.v2))
		{
			continue;
		}

		_union(e.v1, e.v2);
		max += e.w;
	}

	std::cout << max * max - min * min;

	return 0;
}