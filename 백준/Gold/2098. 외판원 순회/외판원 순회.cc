#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0xFFFFFFF;
constexpr int UNINITIALIZED = 2 * INF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int ARR[16][16];
int COST[16][1 << 16];
int N;

int traverse(int node, int visited)
{
    if (visited == (1 << N) - 1)
    {
        return COST[node][visited] = ARR[0][node];
    }

    if (COST[node][visited] < UNINITIALIZED)
    {
        return COST[node][visited];
    }

    for (int v = 0; v < N; ++v)
    {
        if (visited & (1 << v))
        {
            continue;
        }

        COST[node][visited] = min(COST[node][visited], traverse(v, visited | (1 << v)) + ARR[v][node]);
    }

    return COST[node][visited];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < (1 << N); ++j)
        {
            COST[i][j] = UNINITIALIZED;
        }

        for (int j = 0; j < N; ++j)
        {
            std::cin >> ARR[i][j];
            if (ARR[i][j] == 0)
            {
                ARR[i][j] = INF;
            }
        }
    }

    std::cout << traverse(0, 1);

    return 0;
}