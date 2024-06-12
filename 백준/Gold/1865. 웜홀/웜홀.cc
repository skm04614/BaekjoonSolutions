#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

constexpr ll INF = 0x4000000000000000;

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
ll COST[510];
int N;

void init()
{
    COST[1] = 0;
    for (int v = 2; v <= N; ++v)
    {
        COST[v] = INF;
    }
}

bool bf_cycle()
{
    bool decreased = false;
    for (const Edge* e = E; e; e = e->next)
    {
        if (e->v0 == INF)
        {
            continue;
        }

        if (COST[e->v1] <= COST[e->v0] + e->w)
        {
            continue;
        }

        COST[e->v1] = COST[e->v0] + e->w;
        decreased = true;
    }

    return decreased;
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
        std::cin >> N;
        int m, w;
        std::cin >> m >> w;

        int v0, v1;
        ll t;
        for (int i = 1; i <= m; ++i)
        {
            std::cin >> v0 >> v1 >> t;

            E = new Edge{ v0, v1, t, E };
            E = new Edge{ v1, v0, t, E };
        }

        for (int i = 1; i <= w; ++i)
        {
            std::cin >> v0 >> v1 >> t;

            E = new Edge{ v0, v1, -t, E };
        }

        init();
        for (int i = 0; i < N - 1; ++i)
        {
            bf_cycle();
        }

        std::cout << (bf_cycle() ? "YES" : "NO") << '\n';

        delete E;
        E = nullptr;
    }

    return 0;
}