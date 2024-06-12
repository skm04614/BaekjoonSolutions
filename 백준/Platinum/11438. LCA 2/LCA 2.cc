#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

constexpr int LOG_MAX_N = 17;

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
bool VISITED[100100];
int DEPTH[100100];
int PARENT[LOG_MAX_N + 1][100100];
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
        dfs(e->v, depth + 1);
    }
}

void fill_parent(int root)
{
    dfs(root, 0);

    for (int logn = 1; logn <= LOG_MAX_N; logn++)
    {
        for (int v = 1; v <= N; v++)
        {
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

    for (int logn = LOG_MAX_N; logn >= 0; logn--)
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

    for (int logn = LOG_MAX_N; logn >= 0; logn--)
    {
        if (PARENT[logn][v1] != PARENT[logn][v2])
        {
            v1 = PARENT[logn][v1];
            v2 = PARENT[logn][v2];
        }
    }

    return PARENT[0][v1];
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

    fill_parent(1);

    int M;
    std::cin >> M;
    while (M--)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        std::cout << lca(v1, v2) << '\n';
    }

    return 0;
}