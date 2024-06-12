#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

struct Edge
{
    int v0;
    int v1;
    ll w;
    Edge* next;

    Edge(int v0, int v1, ll w, Edge* next) : v0{ v0 }, v1{ v1 }, w{ w }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* E;

inline ll max(ll x, ll y)
{
    return x > y ? x : y;
}

ll MIN = -0x4000000000000000;

ll GAIN[52];
ll COST[52];
ll MAP[52][52];

int N;
int V0;
int V1;

void init()
{
    for (int v = 0; v < N; ++v)
    {
        COST[v] = MIN;
        for (int j = 0; j < N; ++j)
        {
            MAP[v][j] = MIN;
        }
    }
}

void bf_cycle()
{
    for (const Edge* e = E; e; e = e->next)
    {
        if (COST[e->v0] == MIN)
        {
            continue;
        }

        if (COST[e->v0] + e->w > COST[e->v1])
        {
            COST[e->v1] = COST[e->v0] + e->w;
        }
    }
}

bool is_v1_reachable(int v0)
{
    bool visited[55] = {};
    int q[55] = {};
    int lp = -1;
    int rp = -1;

    visited[v0] = true;
    q[++rp] = v0;
    while (rp > lp)
    {
        int v0 = q[++lp];

        for (int v1 = 0; v1 < N; ++v1)
        {
            if (visited[v1] || MAP[v0][v1] == MIN)
            {
                continue;
            }

            visited[v1] = true;
            q[++rp] = v1;
        }
    }

    return visited[V1];
}

bool has_infinite_val()
{
    for (const Edge* e = E; e; e = e->next)
    {
        if (COST[e->v0] == MIN)
        {
            continue;
        }

        if (COST[e->v0] + e->w > COST[e->v1])
        {
            if (is_v1_reachable(e->v1))
            {
                return true;
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
    std::cin >> N >> V0 >> V1 >> M;

    init();

    while (M--)
    {
        int v0, v1;
        ll w;
        std::cin >> v0 >> v1 >> w;

        MAP[v0][v1] = max(MAP[v0][v1], -w);
    }

    for (int i = 0; i < N; ++i)
    {
        std::cin >> GAIN[i];
        for (int j = 0; j < N; ++j)
        {
            if (MAP[j][i] != MIN)
            {
                MAP[j][i] += GAIN[i];
            }
        }
    }
    COST[V0] = GAIN[V0];

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (MAP[i][j] == MIN)
            {
                continue;
            }

            E = new Edge{ i, j, MAP[i][j], E };
        }
    }
    
    for (int i = 0; i < N - 1; ++i)
    {
        bf_cycle();
    }

    if (has_infinite_val())
    {
        std::cout << "Gee";
    }
    else if (COST[V1] == MIN)
    {
        std::cout << "gg";
    }
    else
    {
        std::cout << COST[V1];
    }

    delete E;
    E = nullptr;

    return 0;
}