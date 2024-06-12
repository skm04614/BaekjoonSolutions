#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[200020];
Edge* EDGES[100010];
bool VISITED[100010];
int SIZE[100010];
int N;

void dfs(int node)
{
    SIZE[node] = 1;
    VISITED[node] = true;

    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        dfs(e->v);
        SIZE[node] += SIZE[e->v];
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int root, Q;
    std::cin >> N >> root >> Q;
    for (int i = 0; i < N - 1; ++i)
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

    dfs(root);

    while (Q--)
    {
        int v;
        std::cin >> v;
        std::cout << SIZE[v] << '\n';
    }

    return 0;
}