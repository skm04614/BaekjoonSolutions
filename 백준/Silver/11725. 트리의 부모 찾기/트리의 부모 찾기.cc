#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

constexpr ll MOD = 1000000007;

struct Edge
{
    int v_dst;
    Edge* next;
};
Edge POOL[400400];
Edge* EDGES[200200];
bool VISITED[200200];
int PARENT[200200];
int N;

void dfs(int node)
{
    VISITED[node] = true;

    for (const Edge* edge = EDGES[node]; edge; edge = edge->next)
    {
        if (VISITED[edge->v_dst])
        {
            continue;
        }

        PARENT[edge->v_dst] = node;
        dfs(edge->v_dst);
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (register int i = 1; i < N; i++)
    {
        register int v0, v1;
        std::cin >> v0 >> v1;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v_dst = v1;
        e1.next = EDGES[v0];
        EDGES[v0] = &e1;

        e2.v_dst = v0;
        e2.next = EDGES[v1];
        EDGES[v1] = &e2;
    }

    dfs(1);

    for (register int i = 2; i <= N; i++)
    {
        std::cout << PARENT[i] << '\n';
    }

    return 0;
}