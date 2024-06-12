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

constexpr int N = 0x100;
int C[0x100][0x100];
int F[0x100][0x100];
Adj* ADJ[0x100];

void cleanup()
{
    for (int v = 1; v <= N; ++v)
    {
        delete ADJ[v];
        ADJ[v] = nullptr;
    }
}

int Q[N];
int LP, RP;

int ek(int source, int sink)
{
    int max_flow = 0;
    for (;;)
    {
        LP = RP = 0;
        int origin[N] = {};

        origin[source] = -1;
        Q[++RP] = source;

        while (RP > LP)
        {
            const int start = Q[++LP];
            for (const Adj* adj = ADJ[start]; adj; adj = adj->next)
            {
                if (C[start][adj->v] - F[start][adj->v] > 0 && !origin[adj->v])
                {
                    Q[++RP] = adj->v;
                    origin[adj->v] = start;

                    if (adj->v == sink)
                    {
                        break;
                    }
                }
            }
        }

        if (!origin[sink])
        {
            break;
        }

        int f = 0x7FFFFFFF;
        for (int v = sink; v != source; v = origin[v])
        {
            f = min(f, C[origin[v]][v] - F[origin[v]][v]);
        }

        for (int v = sink; v != source; v = origin[v])
        {
            F[origin[v]][v] += f;
            F[v][origin[v]] -= f;
        }

        max_flow += f;
    }

    return max_flow;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> M;
    for (int i = 0; i < M; ++i)
    {
        char v0, v1;
        int c;
        std::cin >> v0 >> v1 >> c;

        C[v0][v1] += c;
        C[v1][v0] += c;
    }

    for (int v0 = 1; v0 <= N; ++v0)
    {
        for (int v1 = 1; v1 < v0; ++v1)
        {
            if (C[v0][v1] || C[v1][v0])
            {
                ADJ[v0] = new Adj{ v1, ADJ[v0] };
                ADJ[v1] = new Adj{ v0, ADJ[v1] };
            }
        }
    }

    std::cout << ek('A', 'Z');

    cleanup();

    return 0;
}
