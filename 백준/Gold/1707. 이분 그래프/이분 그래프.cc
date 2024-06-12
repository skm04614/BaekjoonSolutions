#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Edge
{
    int v;
    Edge* next;
};

Edge POOL[400400];
Edge* EDGES[200200];
int E;

bool CHECKED[20020];
int DEPTH[20020];
int V;

void clear()
{
    for (int v = 1; v <= V; ++v)
    {
        DEPTH[v] = 0;
    }
}

void reset()
{
    for (int v = 1; v <= V; ++v)
    {
        CHECKED[v] = false;
        DEPTH[v] = 0;
        EDGES[v] = nullptr;
    }
}

bool dfs(int v, int depth)
{
    ++depth;
    if (DEPTH[v])
    {
        return (DEPTH[v] & 1) == (depth & 1);
    }
    CHECKED[v] = true;
    DEPTH[v] = depth;

    for (const Edge* e = EDGES[v]; e; e = e->next)
    {
        if (!dfs(e->v, depth))
        {
            return false;
        }
    }

    return true;
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
        std::cin >> V >> E;

        reset();

        for (int i = 0; i < E; ++i)
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

        bool result = true;
        for (int v = 1; v <= V; ++v)
        {
            if (CHECKED[v])
            {
                continue;
            }

            clear();
            if (!dfs(v, 0))
            {
                result = false;
                break;
            }
        }

        std::cout << (result ? "YES" : "NO") << '\n';
    }

    return 0;
}
