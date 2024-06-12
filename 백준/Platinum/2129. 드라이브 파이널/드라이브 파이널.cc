#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x3FFFFFFF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Edge
{
    int v;
    int w;
    int d;

    Edge* next;

    Edge(int v, int w, int d, Edge* next) : v{ v }, w{ w }, d{ d }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* EDGES[110];
int MIN_TIREDNESS[110];
int COST[110];
int DIST[110];
int N;

void init()
{
    for (int i = 0; i < N; ++i)
    {
        MIN_TIREDNESS[i] = COST[i] = DIST[i] = INF;
    }
}

int S, T;

void bellman_ford()
{
    for (int v0 = 0; v0 < N; ++v0)
    {
        for (const Edge* e = EDGES[v0]; e; e = e->next)
        {
            if (COST[v0] == INF)
            {
                continue;
            }

            const int cost = COST[v0] + e->w;
            const int dist = DIST[v0] + e->d;
            if (cost < COST[e->v])
            {
                COST[e->v] = cost;
                DIST[e->v] = dist;
            }
            else if (cost == COST[e->v])
            {
                DIST[e->v] = min(DIST[e->v], dist);
            }
        }
    }
}

bool VISITED[110];

void reset()
{
    for (int i = 0; i < N; ++i)
    {
        VISITED[i] = false;
    }
}

bool dfs(int node, int dest)
{
    VISITED[node] = true;

    if (node == dest)
    {
        return true;
    }

    for (const Edge* e = EDGES[node]; e; e = e->next)
    {
        if (VISITED[e->v])
        {
            continue;
        }

        if (dfs(e->v, dest))
        {
            return true;
        }
    }

    return false;
}

bool is_negative_inf()
{
    for (int v0 = 0; v0 < N; ++v0)
    {
        for (const Edge* e = EDGES[v0]; e; e = e->next)
        {
            if (COST[v0] == INF)
            {
                continue;
            }

            const int cost = COST[v0] + e->w;
            const int dist = DIST[v0] + e->d;
            if (cost < COST[e->v])
            {
                COST[e->v] = cost;
                DIST[e->v] = dist;

                reset();
                if (dfs(e->v, T))
                {
                    return true;
                }
            }
            else if (cost == COST[e->v])
            {
                DIST[e->v] = min(DIST[e->v], dist);
            }
        }
    }

    return false;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M >> S >> T;
    
    init();

    while (M--)
    {
        int u, v, a, c, b;
        std::cin >> u >> v >> a >> c >> b;
        
        if (a < MIN_TIREDNESS[u])
        {
            delete EDGES[u];
            EDGES[u] = new Edge{ v, a, c, nullptr };
            MIN_TIREDNESS[u] = a;
        }
        else if (a == MIN_TIREDNESS[u])
        {
            EDGES[u] = new Edge{ v, a, c, EDGES[u] };
        }

        if (b < MIN_TIREDNESS[v])
        {
            delete EDGES[v];
            EDGES[v] = new Edge{ u, b, c, nullptr };
            MIN_TIREDNESS[v] = b;
        }
        else if (b == MIN_TIREDNESS[v])
        {
            EDGES[v] = new Edge{ u, b, c, EDGES[v] };
        }
    }

    COST[S] = DIST[S] = 0;
    for (int i = 0; i < N; ++i)
    {
        bellman_ford();
    }

    if (is_negative_inf())
    {
        std::cout << "UNBOUND";
    }
    else if (COST[T] == INF)
    {
        std::cout << "VOID";
    }
    else
    {
        std::cout << COST[T] << ' ' << DIST[T];
    }

    return 0;
}
