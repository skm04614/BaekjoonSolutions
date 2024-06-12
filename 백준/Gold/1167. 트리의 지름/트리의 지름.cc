#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

inline void set(int& x, int& y, int z)
{
    if (y > z)
    {
        return;
    }

    swap(y, z);

    if (y > x)
    {
        swap(x, y);
    }
}

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
bool VISITED[100100];
int COST[100100];
int P;
int N;
int SOL;

void dfs(int node)
{
    VISITED[node] = true;

    int first = 0;
    int second = 0;
    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        dfs(e->v);
        set(first, second, COST[e->v] + e->w);
    }

    COST[node] = first;
    SOL = SOL > first + second ? SOL : first + second;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int v;
        std::cin >> v;

        for (;;)
        {
            int d;
            std::cin >> d;
            if (d == -1)
            {
                break;
            }

            int w;
            std::cin >> w;

            Edge& e = POOL[P++];
            e.v = d;
            e.w = w;
            e.next = EDGES[v];
            EDGES[v] = &e;
        }
    }

    dfs(1);

    std::cout << SOL;

    return 0;
}