#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

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

Edge* EDGES[110];
int IN_DEGREES[110];
bool IS_BASE[110];
int CNT[110][110];
int SOL[110];
int N;

int Q[110];
int LP;
int RP;

void cleanup()
{
	for (int i = 1; i <= N; ++i)
	{
		delete EDGES[i];
		EDGES[i] = nullptr;
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
		int v1, v0, k;
		std::cin >> v1 >> v0 >> k;
		++IN_DEGREES[v1];
		CNT[v1][v0] = k;

		EDGES[v0] = new Edge{ v1, EDGES[v0] };
	}

	for (int i = 1; i <= N; ++i)
	{
		if (IN_DEGREES[i] == 0)
		{
			Q[++RP] = i;
			IS_BASE[i] = true;
		}
	}

	while (RP > LP)
	{
		const int c = Q[++LP];

		for (const Edge* e = EDGES[c]; e; e = e->next)
		{
			if (--IN_DEGREES[e->v] == 0)
			{
				Q[++RP] = e->v;
			}
		}
	}

	SOL[N] = 1;
	for (int i = LP; i >= 1; --i)
	{
		const int v = Q[i];
		if (IS_BASE[v])
		{
			continue;
		}

		const int cnt = SOL[v];
		SOL[v] = 0;
		for (int j = 1; j <= N; ++j)
		{
			SOL[j] += cnt * CNT[v][j];
		}
	}

	for (int v = 1; v <= N; ++v)
	{
		if (SOL[v])
		{
			std::cout << v << ' ' << SOL[v] << '\n';
		}
	}

	cleanup();
	return 0;
}