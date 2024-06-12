#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGN = 14;

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[10010];
Edge* EDGES[10010];
bool HAS_PARENT[10010];
int DEPTH[10010];
int PARENT[MAX_LOGN + 1][10010];
int N;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void init()
{
    for (int i = 1; i <= N; ++i)
    {
        HAS_PARENT[i] = false;
        EDGES[i] = nullptr;
    }
}

void dfs(int root, int depth)
{
    DEPTH[root] = depth;

    for (const Edge* e = EDGES[root]; e; e = e->next)
    {
        dfs(e->v, depth + 1);
        PARENT[0][e->v] = root;
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

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N;
        init();

        for (int i = 0; i < N - 1; ++i)
        {
            int v0, v1;
            std::cin >> v0 >> v1;

            Edge& e = POOL[i];
            e.v = v1;
            e.next = EDGES[v0];
            EDGES[v0] = &e;

            HAS_PARENT[v1] = true;
        }

        int root = 0;
        for (int v = 1; v <= N; ++v)
        {
            if (!HAS_PARENT[v])
            {
                root = v;
                break;
            }
        }

        fill_sparse(root);

        int v1, v2;
        std::cin >> v1 >> v2;
        std::cout << lca(v1, v2) << '\n';
    }

    return 0;
}