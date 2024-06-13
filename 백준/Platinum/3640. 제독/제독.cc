#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;
constexpr int IN_BASE = 0;
constexpr int OUT_BASE = 1000;
constexpr int SIZE = 2010;

inline int min(int x, int y)
{
    return x < y ? x : y;
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

Adj* ADJ[SIZE];
int C[SIZE][SIZE];
int F[SIZE][SIZE];
int W[SIZE][SIZE];

void reset()
{
    for (int i = 0; i < SIZE; ++i)
    {
        delete ADJ[i];
        ADJ[i] = nullptr;

        for (int j = 0; j < SIZE; ++j)
        {
            C[i][j] = F[i][j] = W[i][j] = 0;
        }
    }
}

int COST[SIZE];
int ORIGIN[SIZE];
int Q[SIZE];
int LP, RP;
bool QUEUED[SIZE];

void init()
{
    LP = RP = -1;
    for (int v = 0; v < SIZE; ++v)
    {
        COST[v] = INF;
        ORIGIN[v] = 0;
        QUEUED[v] = false;
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
        ORIGIN[src] = -1;
        Q[++RP % SIZE] = src;

        while (RP > LP)
        {
            const int c = Q[++LP % SIZE];
            QUEUED[c] = false;

            for (const Adj* adj = ADJ[c]; adj; adj = adj->next)
            {
                const int n = adj->v;
                const int cost = COST[c] + adj->w;

                if (COST[n] <= cost || C[c][n] - F[c][n] <= 0)
                {
                    continue;
                }

                COST[n] = cost;
                ORIGIN[n] = c;

                if (QUEUED[n])
                {
                    continue;
                }

                QUEUED[n] = true;
                Q[++RP % SIZE] = n;
            }
        }

        if (!ORIGIN[sink])
        {
            break;
        }

        int flow = INF;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            flow = min(flow, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
        }

        max_flow += flow;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            min_cost += flow * W[ORIGIN[v]][v];
            F[ORIGIN[v]][v] += flow;
            F[v][ORIGIN[v]] -= flow;
        }
    }

    std::cout << min_cost << '\n';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int V, E;
    while (std::cin >> V >> E)
    {
        reset();

        C[IN_BASE + 1][OUT_BASE + 1] = 2;
        C[IN_BASE + V][OUT_BASE + V] = 2;

        for (int v = 2; v < V; ++v)
        {
            C[IN_BASE + v][OUT_BASE + v] = 1;
        }

        for (int i = 1; i <= E; ++i)
        {
            int v0, v1, w;
            std::cin >> v0 >> v1 >> w;

            C[OUT_BASE + v0][IN_BASE + v1] = 1;
            W[OUT_BASE + v0][IN_BASE + v1] = w;
            W[IN_BASE + v1][OUT_BASE + v0] = -w;
        }

        for (int v0 = 0; v0 < SIZE; ++v0)
        {
            for (int v1 = 0; v1 < v0; ++v1)
            {
                if (C[v0][v1] || C[v1][v0])
                {
                    ADJ[v0] = new Adj{ v1, W[v0][v1], ADJ[v0] };
                    ADJ[v1] = new Adj{ v0, W[v1][v0], ADJ[v1] };
                }
            }
        }

        mcmf(IN_BASE + 1, OUT_BASE + V);
    }

    reset();

    return 0;
}
