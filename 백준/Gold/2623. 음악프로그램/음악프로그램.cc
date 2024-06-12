#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int dest;
    Edge* next;
};

Edge POOL[100100];
int P;

int IN_DEGREES[1010];
Edge* EDGES[1010];
int N;

int Q[1010];
int LP;
int RP;

int RECORD[1010];
int R;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    while (M--)
    {
        int K;
        std::cin >> K;
        int src, dest;
        std::cin >> src;
        for (int i = 1; i < K; i++)
        {
            std::cin >> dest;
            Edge& e = POOL[++P];
            e.dest = dest;
            e.next = EDGES[src];
            EDGES[src] = &e;
            ++IN_DEGREES[dest];

            src = dest;
        }
    }

    for (int v = 1; v <= N; v++)
    {
        if (IN_DEGREES[v] == 0)
        {
            Q[RP++] = v;
        }
    }

    while (RP > LP)
    {
        int v = Q[LP++];
        RECORD[R++] = v;

        for (Edge* e = EDGES[v]; e; e = e->next)
        {
            if (--IN_DEGREES[e->dest] == 0)
            {
                Q[RP++] = e->dest;
            }
        }
    }

    if (R == N)
    {
        for (int i = 0; i < R; i++)
        {
            std::cout << RECORD[i] << '\n';
        }
    }
    else
    {
        std::cout << 0;
    }

    return 0;
}