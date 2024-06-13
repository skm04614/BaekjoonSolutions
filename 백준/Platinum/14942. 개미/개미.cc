#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGN = 17;

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
int ENERGY[100100];
bool VISITED[100100];
int PARENT[MAX_LOGN + 1][100100];
int COST[MAX_LOGN + 1][100100];

int N;

void dfs(int node, int depth)
{
    VISITED[node] = true;

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

void fill_sparse()
{
    dfs(1, 0);

    for (int logn = 1; logn <= MAX_LOGN; logn++)
    {
        for (int v = 1; v <= N; v++)
        {
            PARENT[logn][v] = PARENT[logn - 1][PARENT[logn - 1][v]];
            COST[logn][v] = COST[logn - 1][v] + COST[logn - 1][PARENT[logn - 1][v]];
        }
    }
}

void sol(int v)
{
    int energy = ENERGY[v];
    for (int logn = MAX_LOGN; logn >= 0; logn--)
    {
        if (PARENT[logn][v] == 0)
        {
            continue;
        }

        if (COST[logn][v] > energy)
        {
            continue;
        }

        energy -= COST[logn][v];
        v = PARENT[logn][v];
    }

    std::cout << v << '\n';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ENERGY[i];
    }

    for (int i = 1; i <= N - 1; i++)
    {
        int v1, v2, w;
        std::cin >> v1 >> v2 >> w;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.w = e2.w = w;

        e1.v = v2;
        e1.next = EDGES[v1];
        EDGES[v1] = &e1;

        e2.v = v1;
        e2.next = EDGES[v2];
        EDGES[v2] = &e2;
    }

    fill_sparse();

    for (int v = 1; v <= N; v++)
    {
        sol(v);
    }

    return 0;
}