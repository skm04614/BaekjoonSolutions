#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int MAP[11][11];
int N;

void init()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            MAP[i][j] = (i == j) ? 0 : INF;
        }
    }
}

int dfs(int src, int dest, int depth, int credit, int shame, int min_shame)
{
    if (depth > N || credit < 0)
    {
        return INF;
    }

    if (shame >= min_shame)
    {
        return INF;
    }

    if (src == dest)
    {
        return shame;
    }

    for (int v = 1; v <= N; ++v)
    {
        if (v == src || MAP[src][v] == INF)
        {
            continue;
        }


        min_shame = min(min_shame, dfs(v, dest, depth + 1, credit - MAP[src][v], max(shame, MAP[src][v]), min_shame));
    }

    return min_shame;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int m, a, b, c;
    std::cin >> N >> m >> a >> b >> c;
    
    init();

    for (int i = 1; i <= m; ++i)
    {
        int v0, v1, w;
        std::cin >> v0 >> v1 >> w;

        MAP[v0][v1] = MAP[v1][v0] = w;
    }

    int res = dfs(a, b, 0, c, 0, INF);
    std::cout << (res == INF ? -1 : res);

    return 0;
}
