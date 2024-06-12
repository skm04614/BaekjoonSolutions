#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGN = 17;

using ull = unsigned long long;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
int DEPTH[100100];
bool VISITED[100100];
int PARENT[MAX_LOGN + 1][100100];
ull COST[MAX_LOGN + 1][100100];
int N;

void dfs(int node, int depth)
{
    DEPTH[node] = depth;
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

void fill_sparse(int root)
{
    dfs(root, 0);

    for (int logn = 1; logn <= MAX_LOGN; ++logn)
    {
        for (int v = 1; v <= N; ++v)
        {
            COST[logn][v] = COST[logn - 1][v] + COST[logn - 1][PARENT[logn - 1][v]];
            PARENT[logn][v] = PARENT[logn - 1][PARENT[logn - 1][v]];
        }
    }
}

int lca(int v1, int v2)
{
    if (DEPTH[v1] > DEPTH[v2])
    {
        swap(v1, v2);
    }

    for (int logn = MAX_LOGN; logn >= 0; --logn)
    {
        if (DEPTH[v2] - DEPTH[v1] >= (1 << logn))
        {
            v2 = PARENT[logn][v2];
        }
    }

    if (v1 == v2)
    {
        return v1;
    }

    for (int logn = MAX_LOGN; logn >= 0; --logn)
    {
        if (PARENT[logn][v1] != PARENT[logn][v2])
        {
            v1 = PARENT[logn][v1];
            v2 = PARENT[logn][v2];
        }
    }

    return PARENT[0][v1];
}

ull query_cost(int v1, int v2)
{
    if (DEPTH[v1] > DEPTH[v2])
    {
        swap(v1, v2);
    }

    ull cost = 0;

    for (int logn = MAX_LOGN; logn >= 0; --logn)
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

    for (int logn = MAX_LOGN; logn >= 0; --logn)
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

int query_k(int v1, int v2, int k)
{
    int lca_v = lca(v1, v2);

    --k;

    if (k <= DEPTH[v1] - DEPTH[lca_v])
    {
        for (int logn = MAX_LOGN; logn >= 0; --logn)
        {
            if (k >= (1 << logn))
            {
                v1 = PARENT[logn][v1];
                k -= (1 << logn);
            }
        }

        return v1;
    }
    else
    {
        k -= DEPTH[v1] - DEPTH[lca_v];
        k = DEPTH[v2] - DEPTH[lca_v] - k;
        for (int logn = MAX_LOGN; logn >= 0; --logn)
        {
            if (k >= (1 << logn))
            {
                v2 = PARENT[logn][v2];
                k -= (1 << logn);
            }
        }

        return v2;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N - 1; ++i)
    {
        int v1, v2, w;
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

    fill_sparse(1);

    int M;
    std::cin >> M;
    while (M--)
    {
        int opt, v1, v2;
        std::cin >> opt >> v1 >> v2;
        if (opt == 2)
        {
            int k;
            std::cin >> k;
            std::cout << query_k(v1, v2, k) << '\n';
        }
        else
        {
            std::cout << query_cost(v1, v2) << '\n';
        }
    }

    return 0;
}