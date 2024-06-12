#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[2002000];
Edge* EDGES[1001000];
bool VISITED[1001000];
int N;

int SOL;

bool dfs(int node)
{
    VISITED[node] = true;

    int child = 0;
    bool adaptor = true;
    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        ++child;
        adaptor &= dfs(e->v);
    }

    if (child == 0)
    {
        return false;
    }

    if (adaptor == false)
    {
        ++SOL;
        return true;
    }

    return false;
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

    dfs(1);
    std::cout << SOL;


    return 0;
}