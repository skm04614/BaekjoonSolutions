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
int M;

ll COST[550];
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
    bool changed = false;
    for (const Edge* e = E; e; e = e->next)
    {
        if (COST[e->v0] == INF)
        {
            continue;
        }

        if (COST[e->v1] <= COST[e->v0] + e->w)
        {
            continue;
        }

        COST[e->v1] = COST[e->v0] + e->w;
        changed = true;
    }

    return changed;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= M; ++i)
    {
        int v0, v1;
        ll w;
        std::cin >> v0 >> v1 >> w;

        E = new Edge{ v0, v1, w, E };
    }

    init();

    for (int i = 0; i < N - 1; ++i)
    {
        bf_cycle();
    }

    if (bf_cycle())
    {
        std::cout << -1;
    }
    else
    {
        for (int i = 2; i <= N; ++i)
        {
            std::cout << (COST[i] == INF ? -1 : COST[i]) << '\n';
        }
    }

    delete E;
    E = nullptr;

    return 0;
}