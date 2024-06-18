#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;

    Edge(int v, Edge* next) : v{ v }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* EDGES[100100];
int ARR[100100];
int DP[100100];
int N;

void dfs(int node)
{
    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        DP[e->v] = DP[node] + ARR[e->v];
        dfs(e->v);
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int Q;
    std::cin >> N >> Q;
    int v;
    std::cin >> v;
    for (int i = 2; i <= N; ++i)
    {
        std::cin >> v;
        EDGES[v] = new Edge{ i, EDGES[v] };
    }

    while (Q--)
    {
        int v, w;
        std::cin >> v >> w;
        ARR[v] += w;
    }

    dfs(1);

    for (int v = 1; v <= N; ++v)
    {
        std::cout << DP[v] << ' ';
    }

    return 0;
}
