#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

constexpr int SRC = 202;
constexpr int SINK = 203;
constexpr int B_BASE = 100;
constexpr int SIZE = 210;

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

int N, M;

int Q[SIZE];
int ORIGIN[SIZE];
int LP, RP;

void reset()
{
    LP = RP = -1;
    for (int i = 1; i < SIZE; ++i)
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

        Q[++RP] = src;
        ORIGIN[src] = -1;

        bool flag = false;
        while (RP > LP)
        {
            const int start = Q[++LP];
            for (const Adj* adj = ADJ[start]; adj; adj = adj->next)
            {
                if (C[start][adj->v] - F[start][adj->v] > 0 && !ORIGIN[adj->v])
                {
                    ORIGIN[adj->v] = start;
                    Q[++RP] = adj->v;
                    if (adj->v == sink)
                    {
                        flag = true;
                        break;
                    }
                }
            }

            if (flag)
            {
                break;
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
            F[ORIGIN[v]][v] += flow;
            F[v][ORIGIN[v]] -= flow;
        }
    }
    return max_flow;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> C[SRC][i];
    }
    for (int i = 1; i <= M; ++i)
    {
        std::cin >> C[B_BASE + i][SINK];
    }

    for (int i = 1; i <= M; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            int c;
            std::cin >> c;

            C[j][B_BASE + i] = c;
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

    return 0;
}
