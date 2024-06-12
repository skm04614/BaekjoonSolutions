#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGN = 15;

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[60060];
Edge* EDGES[30030];
bool VISITED[30030];
int DEPTH[30030];
int PARENT[MAX_LOGN + 1][30030];
int N;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

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
            PARENT[logn][v] = PARENT[logn - 1][PARENT[logn - 1][v]];
        }
    }
}

int lca_cost(int v1, int v2)
{
    if (DEPTH[v1] > DEPTH[v2])
    {
        swap(v1, v2);
    }

    int sol = 0;

    for (int logn = MAX_LOGN; logn >= 0; --logn)
    {
        if (DEPTH[v2] - DEPTH[v1] >= (1 << logn))
        {
            sol += (1 << logn);
            v2 = PARENT[logn][v2];
        }
    }

    if (v1 == v2)
    {
        return sol;
    }

    for (int logn = MAX_LOGN; logn >= 0; --logn)
    {
        if (PARENT[logn][v2] != PARENT[logn][v1])
        {
            sol += (1 << (logn + 1));
            v2 = PARENT[logn][v2];
            v1 = PARENT[logn][v1];
        }
    }

    return sol + 2;
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
        std::cin >> v1 >> v2;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v = v2;
        e1.next = EDGES[v1];
        EDGES[v1] = &e1;

        e2.v = v1;
        e2.next = EDGES[v2];
        EDGES[v2] = &e2;
    }

    fill_sparse(1);

    int M;
    std::cin >> M;

    int sol = 0;
    int v0 = 1;
    while (M--)
    {
        int v1;
        std::cin >> v1;

        sol += lca_cost(v0, v1);

        v0 = v1;
    }

    std::cout << sol;

    return 0;
}