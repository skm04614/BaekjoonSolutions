#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[10100];
int N;

int find(int v)
{
	if (v == PARENT[v])
	{
		return v;
	}

	return (PARENT[v] = find(PARENT[v]));
}

void _union(int v1, int v2)
{
	v1 = find(v1);
	v2 = find(v2);

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

	bool operator<=(const Edge& other) const
	{
		return w <= other.w;
	}
};

Edge EDGES[100100];
Edge TMP[100100];
int M;

inline void swap(Edge& e1, Edge& e2)
{
	Edge tmp = e1;
	e1 = e2;
	e2 = tmp;
}

void m_sort(Edge* arr, Edge* tmp, int idx0, int idx1)
{
	if (idx0 == idx1)
	{
		return;
	}

	int mid = (idx0 + idx1) / 2;
	m_sort(arr, tmp, idx0, mid);
	m_sort(arr, tmp, mid + 1, idx1);
	
	int left = idx0;
	int right = mid + 1;
	int idx = 0;
	for (;;)
	{
		if (left > mid || right > idx1)
		{
			break;
		}

		if (arr[left] <= arr[right])
		{
			tmp[idx++] = arr[left++];
		}
		else
		{
			tmp[idx++] = arr[right++];
		}
	}

	while (left <= mid)
	{
		tmp[idx++] = arr[left++];
	}

	while (right <= idx1)
	{
		tmp[idx++] = arr[right++];
	}

	for (int i = 0; i < idx; i++)
	{
		arr[idx0 + i] = tmp[i];
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N >> M;
	for (int v = 1; v <= N; v++)
	{
		PARENT[v] = v;
	}

	for (int i = 1; i <= M; i++)
	{
		std::cin >> EDGES[i].v1 >> EDGES[i].v2 >> EDGES[i].w;
	}
	m_sort(EDGES, TMP, 1, M);

	int sol = 0;
	for (int i = 1; i <= M; i++)
	{
		const Edge& edge = EDGES[i];
		if (find(edge.v1) == find(edge.v2))
		{
			continue;
		}

		_union(edge.v1, edge.v2);
		sol += edge.w;
	}
	std::cout << sol;

	return 0;
}