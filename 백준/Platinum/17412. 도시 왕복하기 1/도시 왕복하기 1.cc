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

Adj* ADJ[410];
int C[410][410];
int F[410][410];
int N;

int Q[410];
int LP, RP;
int ORIGIN[410];

void reset()
{
    LP = RP = -1;
    for (int i = 1; i <= N; ++i)
    {
        ORIGIN[i] = 0;
    }
}

int edmonds_karp(int source, int sink)
{
    int max_flow = 0;

    for (;;)
    {
        reset();

        Q[++RP] = source;
        ORIGIN[source] = -1;

        while (RP > LP)
        {
            const int start = Q[++LP];

            for (const Adj* adj = ADJ[start]; adj; adj = adj->next)
            {
                if (C[start][adj->v] - F[start][adj->v] > 0 && !ORIGIN[adj->v])
                {
                    Q[++RP] = adj->v;
                    ORIGIN[adj->v] = start;

                    if (adj->v == sink)
                    {
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
        for (int v = sink; v != source; v = ORIGIN[v])
        {
            f = min(f, C[ORIGIN[v]][v] - F[ORIGIN[v]][v]);
        }

        max_flow += f;

        for (int v = sink; v != source; v = ORIGIN[v])
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

    int P;
    std::cin >> N >> P;
    while (P--)
    {
        int v0, v1;
        std::cin >> v0 >> v1;
        C[v0][v1] += 1;
    }

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

    std::cout << edmonds_karp(1, 2);

    return 0;
}
