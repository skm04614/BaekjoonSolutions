#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int W_BASE = 400;
constexpr int SRC = 805;
constexpr int SINK = 806;
constexpr int SIZE = 810;
constexpr int NEGINF = -0x7FFFFFFF;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

inline int max(int x, int y)
{
	return x > y ? x : y;
}

struct Adj
{
	int v;
	int w;
	Adj* next;

	Adj(int v, int w, Adj* next) : v{ v }, w{ w }, next{ next }
	{

	}

	~Adj()
	{
		delete next;
		next = nullptr;
	}
};

int C[SIZE][SIZE];
int F[SIZE][SIZE];
int W[SIZE][SIZE];

Adj* ADJ[SIZE];
int COST[SIZE];
int ORIGIN[SIZE];
int Q[SIZE];
int LP, RP;
bool QUEUED[SIZE];

void init()
{
	LP = RP = -1;
	for (int i = 0; i < SIZE; ++i)
	{
		COST[i] = NEGINF;
		ORIGIN[i] = 0;
	}
}

void mcmf(int src, int sink)
{
	int max_flow = 0;
	int max_cost = 0;
	for (;;)
	{
		init();

		Q[++RP % SIZE] = src;
		COST[src] = 0;
		while (RP > LP)
		{
			const int c = Q[++LP % SIZE];
			QUEUED[c] = false;

			for (const Adj* adj = ADJ[c]; adj; adj = adj->next)
			{
				const int n = adj->v;
				const int cost = COST[c] + adj->w;
				if (C[c][n] - F[c][n] > 0 && COST[n] < cost)
				{
					COST[n] = cost;
					ORIGIN[n] = c;

					if (!QUEUED[n])
					{
						Q[++RP % SIZE] = n;
						QUEUED[n] = true;
					}
				}
			}
		}

		if (!ORIGIN[sink])
		{
			break;
		}

		int flow = 0x7FFFFFFF;
		for (int v = sink; v != src; v = ORIGIN[v])
		{
			flow = min(flow, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
		}

		max_flow += flow;
		for (int v = sink; v != src; v = ORIGIN[v])
		{
			max_cost += flow * W[ORIGIN[v]][v];
			F[ORIGIN[v]][v] += flow;
			F[v][ORIGIN[v]] -= flow;
		}
	}

	std::cout << max_flow << '\n' << max_cost;
}

void cleanup()
{
	for (int i = 0; i < SIZE; ++i)
	{
		delete ADJ[i];
		ADJ[i] = nullptr;
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	int N, M;
	std::cin >> N >> M;
	for (int i = 1; i <= N; ++i)
	{
		int cnt;
		std::cin >> cnt;
		while (cnt--)
		{
			int j, w;
			std::cin >> j >> w;

			j += W_BASE;

			C[SRC][i] = 1;
			C[i][j] = 1;
			C[j][SINK] = 1;

			W[i][j] = w;
			W[j][i] = -w;
		}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if (C[i][j] || C[j][i])
			{
				ADJ[i] = new Adj{ j, W[i][j], ADJ[i] };
				ADJ[j] = new Adj{ i, W[j][i], ADJ[j] };
			}
		}
	}

	mcmf(SRC, SINK);

	cleanup();
	return 0;
}