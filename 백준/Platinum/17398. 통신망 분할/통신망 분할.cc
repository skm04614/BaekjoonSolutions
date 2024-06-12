#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Query
{
	int v1;
	int v2;
	bool queued;
};

Query QUERIES[100100];
int M;

int QUERY_Q[100100];
int C;

int PARENT[100100];
int SIZE[100100];
int N;

void init()
{
	for (int i = 1; i <= N; i++)
	{
		SIZE[i] = 1;
		PARENT[i] = i;
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
	else if (v1 > v2)
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

	std::cin >> N >> M >> C;

	init();

	for (int i = 1; i <= M; i++)
	{
		std::cin >> QUERIES[i].v1 >> QUERIES[i].v2;
	}

	for (int i = 1; i <= C; i++)
	{
		std::cin >> QUERY_Q[i];
		QUERIES[QUERY_Q[i]].queued = true;
	}

	for (int i = 1; i <= M; i++)
	{
		Query& q = QUERIES[i];
		if (q.queued)
		{
			continue;
		}

		_union(q.v1, q.v2);
	}

	unsigned long long sol = 0;
	for (int i = C; i >= 1; i--)
	{
		Query& q = QUERIES[QUERY_Q[i]];

		int v1 = find(q.v1);
		int v2 = find(q.v2);

		if (v1 == v2)
		{
			continue;
		}

		sol += SIZE[v1] * SIZE[v2];
		_union(v1, v2);
	}
	std::cout << sol;

	return 0;
}