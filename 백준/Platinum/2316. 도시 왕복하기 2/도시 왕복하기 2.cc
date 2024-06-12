#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

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

Adj* ADJ[810];
int C[810][810];
int F[810][810];
int N;

void cleanup()
{
    for (int i = 1; i <= N; ++i)
    {
        delete ADJ[i];
        ADJ[i] = nullptr;
    }
}

int Q[810];
int LP, RP;
int ORIGIN[810];

void reset()
{
    LP = RP = -1;
    for (int v = 1; v <= N; ++v)
    {
        ORIGIN[v] = 0;
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
        while (RP > LP)
        {
            const int s = Q[++LP];
            for (const Adj* adj = ADJ[s]; adj; adj = adj->next)
            {
                if (C[s][adj->v] - F[s][adj->v] > 0 && !ORIGIN[adj->v])
                {
                    ORIGIN[adj->v] = s;
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

inline int in(int v)
{
    return v << 1;
}

inline int out(int v)
{
    return v << 1 | 1;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    while (M--)
    {
        int v0, v1;
        std::cin >> v0 >> v1;
        C[in(v0)][out(v0)] = 1;
        C[in(v1)][out(v1)] = 1;
        C[out(v0)][in(v1)] = 1;
        C[out(v1)][in(v0)] = 1;
    }

    N = 2 * (N + 1);
    for (int i = 1; i <= N; ++i)
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

    std::cout << edmonds_karp(out(1), in(2));

    cleanup();

    return 0;
}
