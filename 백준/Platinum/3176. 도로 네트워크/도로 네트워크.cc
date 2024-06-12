#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

constexpr int LOG_MAXN = 17;

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[200200];
Edge* EDGES[100100];
bool VISITED[100100];
int DEPTH[100100];
int MIN_COST[LOG_MAXN + 1][100100];
int MAX_COST[LOG_MAXN + 1][100100];
int PARENT[LOG_MAXN + 1][100100];
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

        MIN_COST[0][e->v] = MAX_COST[0][e->v] = e->w;
        PARENT[0][e->v] = node;
        dfs(e->v, depth + 1);
    }
}

void fill_sparse(int root)
{
    dfs(root, 0);

    for (int logn = 1; logn <= LOG_MAXN; logn++)
    {
        for (int v = 1; v <= N; v++)
        {
            PARENT[logn][v] = PARENT[logn - 1][PARENT[logn - 1][v]];
            MIN_COST[logn][v] = min(MIN_COST[logn - 1][v], MIN_COST[logn - 1][PARENT[logn - 1][v]]);
            MAX_COST[logn][v] = max(MAX_COST[logn - 1][v], MAX_COST[logn - 1][PARENT[logn - 1][v]]);
        }
    }
}

void sol(int v1, int v2)
{
    if (DEPTH[v1] > DEPTH[v2])
    {
        swap(v1, v2);
    }

    int min_cost = 0x7FFFFFFF;
    int max_cost = 0;

    for (int logn = LOG_MAXN; logn >= 0; logn--)
    {
        if (DEPTH[v2] - DEPTH[v1] >= (1 << logn))
        {
            min_cost = min(min_cost, MIN_COST[logn][v2]);
            max_cost = max(max_cost, MAX_COST[logn][v2]);

            v2 = PARENT[logn][v2];
        }
    }

    if (v1 == v2)
    {
        std::cout << min_cost << ' ' << max_cost << '\n';
        return;
    }

    for (int logn = LOG_MAXN; logn >= 0; logn--)
    {
        if (PARENT[logn][v1] != PARENT[logn][v2])
        {
            min_cost = min(min(min_cost, MIN_COST[logn][v1]), MIN_COST[logn][v2]);
            max_cost = max(max(max_cost, MAX_COST[logn][v1]), MAX_COST[logn][v2]);

            v1 = PARENT[logn][v1];
            v2 = PARENT[logn][v2];
        }
    }

    min_cost = min(min(min_cost, MIN_COST[0][v1]), MIN_COST[0][v2]);
    max_cost = max(max(max_cost, MAX_COST[0][v1]), MAX_COST[0][v2]);
    std::cout << min_cost << ' ' << max_cost << '\n';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N - 1; i++)
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
        int v1, v2;
        std::cin >> v1 >> v2;
        sol(v1, v2);
    }

    return 0;
}