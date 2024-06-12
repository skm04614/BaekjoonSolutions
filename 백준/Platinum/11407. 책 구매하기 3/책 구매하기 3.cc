#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

// SRC -> STORE -> CUSTOMER -> SINK

constexpr int SRC = 205;
constexpr int SINK = 206;
constexpr int SIZE = 210;
constexpr int C_BASE = 100;
constexpr int INF = 0x7FFFFFFF;

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

void cleanup()
{
    for (int v = 0; v < SIZE; ++v)
    {
        delete ADJ[v];
        ADJ[v] = nullptr;
    }
}

int COST[SIZE];
int ORIGIN[SIZE];
int Q[SIZE];
bool QUEUED[SIZE];
int LP, RP;

void init()
{
    LP = RP = -1;
    for (int v = 0; v < SIZE; ++v)
    {
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

                if (cost >= COST[n] || C[c][n] - F[c][n] <= 0)
                {
                    continue;
                }

                ORIGIN[n] = c;
                COST[n] = cost;
                if (QUEUED[n])
                {
                    continue;
                }

                Q[++RP % SIZE] = n;
                QUEUED[n] = true;
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

    std::cout << max_flow << '\n' << min_cost;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n, m;
    std::cin >> n >> m;
    for (int customer = C_BASE + 1; customer <= C_BASE + n; ++customer)
    {
        std::cin >> C[customer][SINK];
    }

    for (int store = 1; store <= m; ++store)
    {
        std::cin >> C[SRC][store];
    }

    for (int store = 1; store <= m; ++store)
    {
        for (int customer = C_BASE + 1; customer <= C_BASE + n; ++customer)
        {
            std::cin >> C[store][customer];
        }
    }

    for (int store = 1; store <= m; ++store)
    {
        for (int customer = C_BASE + 1; customer <= C_BASE + n; ++customer)
        {
            std::cin >> W[store][customer];
            W[customer][store] = -W[store][customer];
        }
    }

    /**/
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
