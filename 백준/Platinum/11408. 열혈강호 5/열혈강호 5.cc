#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>


constexpr int INF = 0x7FFFFFFF;
constexpr int W_BASE = 400;
constexpr int SRC = 805;
constexpr int SINK = 806;
constexpr int SIZE = 810;

inline int min(int x, int y)
{
	return x < y ? x : y;
}

struct Adj
{
	int v;
	int w;
	Adj* next;

	Adj(int v, int w, Adj* next) : v{v}, w{w}, next{next}
	{
	}

	~Adj()
	{
		delete next;
		next = nullptr;
	}
};

Adj* ADJ[SIZE];
int C[SIZE][SIZE];
int F[SIZE][SIZE];
int W[SIZE][SIZE];

int COST[SIZE];
int ORIGIN[SIZE];
int Q[SIZE];
int LP, RP;
bool QUEUED[SIZE];

void init()
{
	LP = RP = 0;
	for (int v = 0; v < SIZE; ++v)
	{
		COST[v] = INF;
		ORIGIN[v] = 0;
		QUEUED[v] = false;
	}
}

void cleanup()
{
	for (int v = 0; v < SIZE; ++v)
	{
		delete ADJ[v];
		ADJ[v] = nullptr;
	}
}

void mcmf(int src, int sink)
{
	int max_flow = 0;
	int min_cost = 0;
	for (;;)
	{
		init();

		COST[src] = 0;
		Q[++RP % SIZE] = src;
		while (RP > LP)
		{
			const int c = Q[++LP % SIZE];
			QUEUED[c] = false;

			for (const Adj* adj = ADJ[c]; adj; adj = adj->next)
			{
				const int n = adj->v;
				if (COST[n] > COST[c] + adj->w && C[c][n] - F[c][n] > 0)
				{
					COST[n] = COST[c] + adj->w;

					ORIGIN[n] = c;
					if (!QUEUED[n])
					{
						QUEUED[n] = true;
						Q[++RP % SIZE] = n;
					}
				}
			}
		}

		if (!ORIGIN[sink])
		{
			break;
		}

		int flow = INF;
		int cost = COST[sink];
		for (int v = sink; v != src; v = ORIGIN[v])
		{
			flow = min(flow, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
		}

		max_flow += flow;
		min_cost += cost;

		for (int v = sink; v != src; v = ORIGIN[v])
		{
			F[ORIGIN[v]][v] += flow;
			F[v][ORIGIN[v]] -= flow;
		}
	}

	std::cout << max_flow << '\n' << min_cost;
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

		C[SRC][i] = 1;
		W[SRC][i] = W[i][SRC] = 0;

		while (cnt--)
		{
			int j, w;
			std::cin >> j >> w;
			
			j += W_BASE;

			C[i][j] = 1;
			W[i][j] = w;
			W[j][i] = -w;

			C[j][SINK] = 1;
			W[j][SINK] = W[SINK][j] = 0;
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