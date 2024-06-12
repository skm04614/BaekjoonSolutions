#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int T[10010];
int N;

struct Edge
{
    int v;

    Edge* next;

    Edge(int v, Edge* next) : v{ v }, next{ next }
    {

    }
};

int IN_DEGREES[10010];
int FINAL[10010];
Edge* EDGES[10010];

int Q[10010];
int LP;
int RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> T[i];
        int m;
        std::cin >> m;
        while (m--)
        {
            int v;
            std::cin >> v;

            EDGES[v] = new Edge{ i, EDGES[v] };
            ++IN_DEGREES[i];
        }
    }

    int sol = 0;

    for (int v = 1; v <= N; ++v)
    {
        if (IN_DEGREES[v] == 0)
        {
            FINAL[v] = T[v];
            sol = max(sol, FINAL[v]);
            Q[++RP] = v;
        }
    }

    while (RP > LP)
    {
        const int v = Q[++LP];

        for (const Edge* e = EDGES[v]; e; e = e->next)
        {
            FINAL[e->v] = max(FINAL[e->v], FINAL[v]);

            if (--IN_DEGREES[e->v] == 0)
            {
                FINAL[e->v] += T[e->v];
                sol = max(sol, FINAL[e->v]);
                Q[++RP] = e->v;
            }
        }
    }
    std::cout << sol;

    for (int i = 1; i <= N; ++i)
    {
        delete EDGES[i];
        EDGES[i] = nullptr;
    }

    return 0;
}