#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int LOG2_MAX_N = 17;

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[100100];
Edge* EDGES[50050];
bool VISITED[50050];
int DEPTH[50050];
int PARENT[LOG2_MAX_N][50050];
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

void fill_parent(int root)
{
    dfs(root, 0);

    for (int n = 1; n < LOG2_MAX_N; ++n)
    {
        for (int v = 1; v <= N; v++)
        {
            PARENT[n][v] = PARENT[n - 1][PARENT[n - 1][v]];
        }
    }
}

int lca(int v0, int v1)
{
    if (DEPTH[v0] > DEPTH[v1])
    {
        swap(v0, v1);
    }

    for (int n = LOG2_MAX_N - 1; n >= 0; n--)
    {
        if (DEPTH[v1] - DEPTH[v0] >= (1 << n))
        {
            v1 = PARENT[n][v1];
        }
    }

    if (v1 == v0)
    {
        return v0;
    }

    for (int n = LOG2_MAX_N - 1; n >= 0; n--)
    {
        if (PARENT[n][v0] != PARENT[n][v1])
        {
            v0 = PARENT[n][v0];
            v1 = PARENT[n][v1];
        }
    }

    return PARENT[0][v0];
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