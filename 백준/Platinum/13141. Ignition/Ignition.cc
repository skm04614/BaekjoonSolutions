#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

constexpr int INF = 0x7FFFFFFF;

struct Edge
{
    int v1;
    int v2;
    int w;

    Edge* next;

    Edge(int v1, int v2, int w, Edge* next) : v1{ v1 }, v2{ v2 }, w{ w }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* EDGES[10010];

int MAP[210][210];
int COST[210][210];
int N;
int M;

template <typename T>
inline T min(T x, T y)
{
    return x < y ? x : y;
}

template <typename T>
inline T max(T x, T y)
{
    return x > y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            COST[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (int i = 1; i <= M; ++i)
    {
        int v1, v2, w;
        std::cin >> v1 >> v2 >> w;
        
        if (v1 != v2)
        {
            COST[v1][v2] = min(COST[v1][v2], w);
            COST[v2][v1] = min(COST[v2][v1], w);
        }

        EDGES[v1] = new Edge{ v1, v2, w, EDGES[v1] };
        EDGES[v2] = new Edge{ v2, v1, w, EDGES[v2] };
    }

    for (int k = 1; k <= N; ++k)
    {
        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                if (COST[i][k] == INF || COST[k][j] == INF)
                {
                    continue;
                }

                COST[i][j] = min(COST[i][j], COST[i][k] + COST[k][j]);
            }
        }
    }

    double T = static_cast<double>(INF);
    for (int s = 1; s <= N; ++s)
    {
        const int* cost = COST[s];

        double t = 0;
        for (int v = 1; v <= N; ++v)
        {
            for (const Edge* e = EDGES[v]; e; e = e->next)
            {
                if (cost[e->v1] > cost[e->v2])
                {
                    continue;
                }
                int dw = e->w - (cost[e->v2] - cost[e->v1]);

                double t_tmp = cost[e->v2] + static_cast<double>(dw) / 2;

                t = max(t, t_tmp);
            }
        }

        T = min(T, t);
    }

    std::cout << std::fixed << std::setprecision(1) << T;

    return 0;
}