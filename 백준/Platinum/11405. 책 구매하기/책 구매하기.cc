#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int SRC = 205;
constexpr int SINK = 206;
constexpr int SIZE = 210;
constexpr int B_BASE = 100;
constexpr int INF = 0x7FFFFFFF;

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
    for (int v = 0; v < SIZE; ++v)
    {
        QUEUED[v] = false;
        COST[v] = INF;
        ORIGIN[v] = 0;
    }
}

void mcmf(int src, int sink)
{
    int max_flow = 0;
    int min_cost = 0;
    for (;;)
    {
        init();

        ORIGIN[src] = -1;
        COST[src] = 0;
        Q[++RP % SIZE] = src;
        while (RP > LP)
        {
            const int c = Q[++LP % SIZE];
            QUEUED[c] = false;

            for (const Adj* adj = ADJ[c]; adj; adj = adj->next)
            {
                const int n = adj->v;
                const int cost = COST[c] + adj->w;
                if (C[c][n] - F[c][n] > 0 && COST[n] > cost)
                {
                    ORIGIN[n] = c;
                    COST[n] = cost;

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

        int flow = INF;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            flow = min(flow, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
        }

        max_flow += flow;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            min_cost += W[ORIGIN[v]][v] * flow;
            F[ORIGIN[v]][v] += flow;
            F[v][ORIGIN[v]] -= flow;
        }
    }

    std::cout << min_cost;
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
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    for (int i = 1; i <= N; ++i)
    {
        std::cin >> C[i][SINK];
    }

    for (int i = B_BASE + 1; i <= B_BASE + M; ++i)
    {
        std::cin >> C[SRC][i];
        for (int j = 1; j <= N; ++j)
        {
            C[i][j] = INF;
        }
    }

    for (int i = B_BASE + 1; i <= B_BASE + M; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            std::cin >> W[i][j];
            W[j][i] = -W[i][j];
        }
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

    mcmf(SRC, SINK);

    cleanup();

    return 0;
}
