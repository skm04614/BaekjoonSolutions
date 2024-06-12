#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MIN = -0x7FFFFFFF;

int max(int x, int y)
{
    return x > y ? x : y;
}

int COST[110];
int MAP[110][110];
int N;

struct Edge
{
    int v0;
    int v1;
    int w;
    Edge* next;

    Edge(int v0, int v1, int w, Edge* next) : v0{ v0 }, v1{ v1 }, w{ w }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* E;

void init()
{
    for (int i = 1; i <= N; ++i)
    {
        COST[i] = MIN;
        for (int j = 1; j <= N; ++j)
        {
            MAP[i][j] = MIN;
        }
    }
    COST[1] = 0;
}

int REC[101];

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
            REC[e->v1] = e->v0;
        }
    }
}

bool is_dest_reachable(int node)
{
    bool visited[101] = {};
    int q[101] = {};
    int lp = -1;
    int rp = -1;

    q[++rp] = node;
    visited[node] = true;
    while (rp > lp)
    {
        int c = q[++lp];
        for (int i = 1; i <= N; ++i)
        {
            if (MAP[c][i] == MIN || visited[i])
            {
                continue;
            }

            visited[i] = true;
            q[++rp] = i;
        }
    }

    return visited[N];
}

bool has_fallen_in_cycle()
{
    for (const Edge* e = E; e; e = e->next)
    {
        if (COST[e->v0] == MIN)
        {
            continue;
        }

        if (COST[e->v0] + e->w > COST[e->v1])
        {
            if (is_dest_reachable(e->v1))
            {
                return false;
            }
        }
    }

    return true;
}

void print_record(int node)
{
    if (node == 0)
    {
        return;
    }

    print_record(REC[node]);

    std::cout << node << ' ';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    
    init();

    while (M--)
    {
        int v0, v1, w;
        std::cin >> v0 >> v1 >> w;

        MAP[v0][v1] = max(MAP[v0][v1], w);
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (MAP[i][j] != MIN)
            {
                E = new Edge{ i, j, MAP[i][j], E };
            }
        }
    }

    for (int i = 0; i < N - 1; ++i)
    {
        bf_cycle();
    }

    if (COST[N] == MIN || !has_fallen_in_cycle())
    {
        std::cout << -1;
    }
    else
    {
        print_record(N);
    }

    delete E;
    E = nullptr;

    return 0;
}