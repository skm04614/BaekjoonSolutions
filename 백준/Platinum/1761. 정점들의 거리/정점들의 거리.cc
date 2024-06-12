#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

constexpr int MAX_LOGN = 16;

using uint = unsigned int;
using ull = unsigned long long;

struct Edge
{
    int v;
    uint w;
    Edge* next;
};

Edge POOL[80080];
Edge* EDGES[40040];
bool VISITED[40040];
int DEPTH[40040];
int PARENT[MAX_LOGN + 1][40040];
uint COST[MAX_LOGN + 1][40040];
int N;

void dfs(int node, int depth)
{
    VISITED[node] = true;
    DEPTH[node] = depth;

    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        PARENT[0][e->v] = node;
        COST[0][e->v] = e->w;
        dfs(e->v, depth + 1);
    }
}

void set_parent(int root)
{
    dfs(root, 0);

    for (int logn = 1; logn <= MAX_LOGN; logn++)
    {
        for (int v = 1; v <= N; v++)
        {
            PARENT[logn][v] = PARENT[logn - 1][PARENT[logn - 1][v]];
            COST[logn][v] = COST[logn - 1][v] + COST[logn - 1][PARENT[logn - 1][v]];
        }
    }
}

ull lca_dist(int v1, int v2)
{
    if (DEPTH[v1] > DEPTH[v2])
    {
        swap(v1, v2);
    }

    ull cost = 0;
    for (int logn = MAX_LOGN; logn >= 0; logn--)
    {
        if (DEPTH[v2] - DEPTH[v1] >= (1 << logn))
        {
            cost += COST[logn][v2];
            v2 = PARENT[logn][v2];
        }
    }

    if (v1 == v2)
    {
        return cost;
    }

    for (int logn = MAX_LOGN; logn >= 0; logn--)
    {
        if (PARENT[logn][v1] != PARENT[logn][v2])
        {
            cost += COST[logn][v1] + COST[logn][v2];
            v1 = PARENT[logn][v1];
            v2 = PARENT[logn][v2];
        }
    }

    return cost + COST[0][v1] + COST[0][v2];
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N - 1; i++)
    {
        int v1, v2;
        uint w;
        std::cin >> v1 >> v2 >> w;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v = v2;
        e1.w = w;
        e1.next = EDGES[v1];
        EDGES[v1] = &e1;

        e2.v = v1;
        e2.w = w;
        e2.next = EDGES[v2];
        EDGES[v2] = &e2;
    }

    set_parent(1);

    int M;
    std::cin >> M;
    while (M--)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        std::cout << lca_dist(v1, v2) << '\n';
    }



    return 0;
}