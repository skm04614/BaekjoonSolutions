#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N;
int M;
int V0, V1;

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
Edge* REV_EDGES[100100];
bool VISITED_REV[100100];
int IN_DEGREES[100100];
int COST[100100];
int COUNT[100100];

int Q[100100];
int LP;
int RP;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int v0, v1, w;
        std::cin >> v0 >> v1 >> w;

        Edge& e = POOL[i << 1];

        e.v = v1;
        e.w = w;
        e.next = EDGES[v0];
        EDGES[v0] = &e;

        ++IN_DEGREES[v1];

        Edge& e_r = POOL[i << 1 | 1];

        e_r.v = v0;
        e_r.w = w;
        e_r.next = REV_EDGES[v1];
        REV_EDGES[v1] = &e_r;
    }
    std::cin >> V0 >> V1;

    Q[++RP] = V0;
    while (RP > LP)
    {
        int v = Q[++LP];

        for (const Edge* e = EDGES[v]; e; e = e->next)
        {
            if (COST[v] + e->w > COST[e->v])
            {
                COST[e->v] = COST[v] + e->w;
                COUNT[e->v] = 1;
            }
            else if (COST[v] + e->w == COST[e->v])
            {
                ++COUNT[e->v];
            }

            if (--IN_DEGREES[e->v])
            {
                continue;
            }

            Q[++RP] = e->v;
        }
    }

    RP = LP = 0;
    Q[++RP] = V1;

    int SOL = COUNT[V1];
    VISITED_REV[V1] = true;
    while (RP > LP)
    {
        int v = Q[++LP];

        for (const Edge* e = REV_EDGES[v]; e; e = e->next)
        {
            if (COST[v] - e->w != COST[e->v] || VISITED_REV[e->v])
            {
                continue;
            }

            VISITED_REV[e->v] = true;
            SOL += COUNT[e->v];
            Q[++RP] = e->v;
        }
    }

    std::cout << COST[V1] << '\n' << SOL;

    return 0;
}