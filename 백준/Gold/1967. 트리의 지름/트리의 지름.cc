#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

struct Edge
{
    int v;
    int w;
    Edge* next;
};

Edge POOL[20020];
Edge* EDGES[10010];
int N;

bool VISITED[10010];
int COST[10010];

int SOL;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void set(int& first, int& second, int val)
{
    if (second > val)
    {
        return;
    }

    swap(second, val);

    if (second > first)
    {
        swap(first, second);
    }
}

void dfs(int node)
{
    VISITED[node] = true;

    int first = 0;
    int second = 0;
    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        dfs(e->v);
        set(first, second, COST[e->v] + e->w);
    }

    SOL = SOL > (first + second) ? SOL : (first + second);

    COST[node] = first;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i < N; i++)
    {
        int v0, v1, w;
        std::cin >> v0 >> v1 >> w;

        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        e1.v = v1;
        e1.w = w;
        e1.next = EDGES[v0];
        EDGES[v0] = &e1;

        e2.v = v0;
        e2.w = w;
        e2.next = EDGES[v1];
        EDGES[v1] = &e2;
    }

    dfs(1);
    std::cout << SOL;

    return 0;
}