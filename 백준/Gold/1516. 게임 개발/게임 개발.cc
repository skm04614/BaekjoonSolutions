#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Edge
{
	int v;
	Edge* next;

	Edge(int v, Edge* next) : v{ v }, next{ next }
	{

	}

	~Edge()
	{
		delete next;
		next = nullptr;
	}
};

Edge* EDGES[510];
int IN_DEGREE[510];
int SOL[510];
int T[510];
int N;

int Q[510];
int LP, RP;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	std::cin >> N;
	for (int i = 1; i <= N; ++i)
	{
		std::cin >> T[i];

		int v;
		for (;;)
		{
			std::cin >> v;
			if (v == -1)
			{
				break;
			}

			EDGES[v] = new Edge{ i, EDGES[v] };
			++IN_DEGREE[i];
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		if (IN_DEGREE[i] == 0)
		{
			Q[++RP] = i;
		}
	}

	while (RP > LP)
	{
		const int c = Q[++LP];
		SOL[c] += T[c];

		for (const Edge* e = EDGES[c]; e; e = e->next)
		{
			const int n = e->v;

			SOL[n] = max(SOL[n], SOL[c]);

			if (--IN_DEGREE[n] == 0)
			{
				Q[++RP] = n;
			}
		}
	}

	for (int i = 1; i <= N; ++i)
	{
		std::cout << SOL[i] << '\n';
	}

	return 0;
}