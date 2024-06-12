#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int B_BASE = 50;
constexpr int SRC = 105;
constexpr int SINK = 106;
constexpr int SIZE = 110;
constexpr int INF = 0x7FFFFFFF;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

bool cmp(int n, int m, bool is_min)
{
    return is_min ? n <= m : n >= m;
}

int fine(int t0, int t1, int t, int max_fine)
{
    int dt = t1 - t0;
    if (dt >= t)
    {
        return 0;
    }

    int tmp = (t - dt);
    return min(max_fine, tmp * tmp);
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

int A[SIZE];
int B[SIZE];
int N;
int T;
int MAX_F;

Adj* ADJ[SIZE];
int C[SIZE][SIZE];
int F[SIZE][SIZE];
int W[SIZE][SIZE];

int COST[SIZE];
int Q[SIZE];
int ORIGIN[SIZE];
bool QUEUED[SIZE];
int LP, RP;

void cleanup()
{
    for (int v = 0; v < SIZE; ++v)
    {
        delete ADJ[v];
        ADJ[v] = nullptr;
    }
}

void reset()
{
    for (int v0 = 0; v0 < SIZE; ++v0)
    {
        for (int v1 = 0; v1 < SIZE; ++v1)
        {
            F[v0][v1] = 0;
        }
    }
}

void init(bool is_min)
{
    LP = RP = -1;
    for (int v = 0; v < SIZE; ++v)
    {
        ORIGIN[v] = 0;
        QUEUED[v] = false;
        COST[v] = is_min ? INF : -INF;
    }
}

bool mcmf(int src, int sink, bool is_min)
{
    reset();

    int max_flow = 0;
    int final_cost = 0;
    for (;;)
    {
        init(is_min);

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

                if (cmp(COST[n], cost, is_min) || C[c][n] - F[c][n] <= 0)
                {
                    continue;
                }

                ORIGIN[n] = c;
                COST[n] = cost;
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
            final_cost += flow * W[ORIGIN[v]][v];
            F[ORIGIN[v]][v] += flow;
            F[v][ORIGIN[v]] -= flow;
        }
    }

    if (max_flow == N)
    {
        std::cout << final_cost << ' ';
        return true;
    }

    std::cout << -1;
    return false;
}

void sol(int src, int sink)
{
    if (mcmf(SRC, SINK, true) == false)
    {
        return;
    }

    mcmf(SRC, SINK, false);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> A[i];
        C[SRC][i] = 1;
    }

    for (int j = B_BASE + 1; j <= B_BASE + N; ++j)
    {
        std::cin >> B[j];
        C[j][SINK] = 1;
    }

    std::cin >> T >> MAX_F;

    for (int i = 1; i <= N; ++i)
    {
        for (int j = B_BASE + 1; j <= B_BASE + N; ++j)
        {
            if (A[i] < B[j])
            {
                C[i][j] = 1;
                W[i][j] = fine(A[i], B[j], T, MAX_F);
                W[j][i] = -W[i][j];
            }
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

    sol(SRC, SINK);

    cleanup();
    return 0;
}
