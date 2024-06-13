#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int D_BASE = 200;
constexpr int SRC = 305;
constexpr int SINK = 306;
constexpr int SIZE = 310;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Adj
{
    int v;
    Adj* next;

    Adj(int v, Adj* next) : v{ v }, next{ next }
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
Adj* ADJ[SIZE];

int Q[SIZE];
int LP, RP;
int ORIGIN[SIZE];

void reset()
{
    LP = RP = -1;
    for (int i = 0; i < SIZE; ++i)
    {
        ORIGIN[i] = 0;
    }
}

int edmonds_karp(int src, int sink)
{
    int max_flow = 0;
    for (;;)
    {
        reset();

        ORIGIN[src] = -1;
        Q[++RP] = src;
        while (RP > LP)
        {
            const int c = Q[++LP];
            for (Adj* adj = ADJ[c]; adj; adj = adj->next)
            {
                if (C[c][adj->v] - F[c][adj->v] > 0 && !ORIGIN[adj->v])
                {
                    ORIGIN[adj->v] = c;
                    Q[++RP] = adj->v;
                    if (adj->v == sink)
                    {
                        RP = LP;
                        break;
                    }
                }
            }
        }

        if (!ORIGIN[sink])
        {
            break;
        }

        int f = 0x7FFFFFFF;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            f = min(f, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
        }

        max_flow += f;
        for (int v = sink; v != src; v = ORIGIN[v])
        {
            F[ORIGIN[v]][v] += f;
            F[v][ORIGIN[v]] -= f;
        }
    }
    return max_flow;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, K, D;
    std::cin >> N >> K >> D;
    for (int n = 1; n <= N; ++n)
    {
        C[SRC][n] = K;
    }
    
    for (int d = 1; d <= D; ++d)
    {
        std::cin >> C[D_BASE + d][SINK];
    }

    for (int n = 1; n <= N; ++n)
    {
        int cnt;
        std::cin >> cnt;
        while (cnt--)
        {
            int d;
            std::cin >> d;
            C[n][D_BASE + d] = 1;
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (C[i][j] || C[j][i])
            {
                ADJ[i] = new Adj{ j, ADJ[i] };
                ADJ[j] = new Adj{ i, ADJ[j] };
            }
        }
    }

    std::cout << edmonds_karp(SRC, SINK);

    return 0;
}
