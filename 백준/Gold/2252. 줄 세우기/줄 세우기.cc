#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int dest;
    Edge* next;
};

Edge POOL[100100];
int M;

Edge* EDGES[33000];
int IN_DEGREE[33000];
int N;

int Q[33000];
int LP;
int RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (register int i = 1; i <= M; i++)
    {
        int src;
        std::cin >> src >> POOL[i].dest;
        POOL[i].next = EDGES[src];

        EDGES[src] = &POOL[i];
        ++IN_DEGREE[POOL[i].dest];
    }

    LP = RP = -1;

    for (register int v = 1; v <= N; v++)
    {
        if (IN_DEGREE[v] == 0)
        {
            Q[++RP] = v;
        }
    }

    while (RP > LP)
    {
        int v0 = Q[++LP];
        std::cout << v0 << ' ';

        for (register Edge* edge = EDGES[v0]; edge; edge = edge->next)
        {
            if (--IN_DEGREE[edge->dest] == 0)
            {
                Q[++RP] = edge->dest;
            }
        }
    }

    return 0;
}