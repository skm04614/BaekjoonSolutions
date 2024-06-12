#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

int PARENT[1010];
int N;

void init(void)
{
    for (register int v = 1; v <= N; v++)
    {
        PARENT[v] = v;
    }
}

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
    v1 = find(v1);
    v2 = find(v2);

    if (v1 < v2)
    {
        PARENT[v2] = v1;
    }
    else
    {
        PARENT[v1] = v2;
    }
}

struct Edge
{
    int v1;
    int v2;
    int w;
};
Edge EDGES[10100];
int M;

ull sol(int sidx)
{
    init();

    ull res = 0;
    for (register int i = sidx; i < M; i++)
    {
        const Edge& edge = EDGES[i];

        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        res += edge.w;
    }

    for (register int v = 1; v <= N; v++)
    {
        if (find(v) != 1)
        {
            res = 0;
            break;
        }
    }
    
    return res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int K;
    std::cin >> N >> M >> K;
    for (register int i = 0; i < M; i++)
    {
        Edge& edge = EDGES[i];

        std::cin >> edge.v1 >> edge.v2;
        edge.w = i + 1;
    }

    for (register int i = 0; i < K; i++)
    {
        std::cout << sol(i) << ' ';
    }

    return 0;
}