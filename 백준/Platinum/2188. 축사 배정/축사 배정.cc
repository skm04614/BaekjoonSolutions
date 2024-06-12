#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int SRC = 405;
constexpr int SINK = 406;
constexpr int SIZE = 410;
constexpr int B_BASE = 200;

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

Adj* ADJ[SIZE];
int C[SIZE][SIZE];
int F[SIZE][SIZE];

void cleanup()
{
    for (int i = 0; i < SIZE; ++i)
    {
        delete ADJ[i];
        ADJ[i] = nullptr;
    }
}

int Q[SIZE];
int RP, LP;
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
                const int n = adj->v;
                if (C[c][n] - F[c][n] > 0 && !ORIGIN[n])
                {
                    ORIGIN[n] = c;
                    Q[++RP] = n;
                    if (n == sink)
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

    int N, M;
    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        C[SRC][i] = 1;

        int cnt;
        std::cin >> cnt;
        while (cnt--)
        {
            int v;
            std::cin >> v;
            C[i][B_BASE + v] = 1;
            C[B_BASE + v][SINK] = 1;
        }
    }

    for (int i = 1; i < SIZE; ++i)
    {
        for (int j = 1; j < i; ++j)
        {
            if (C[i][j] || C[j][i])
            {
                ADJ[i] = new Adj{ j, ADJ[i] };
                ADJ[j] = new Adj{ i, ADJ[j] };
            }
        }
    }

    std::cout << edmonds_karp(SRC, SINK);

    cleanup();
    return 0;
}
