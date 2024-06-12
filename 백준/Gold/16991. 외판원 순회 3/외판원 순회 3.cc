#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>
#include <cmath>

double INF = 0x7FFFFFFF;

int X[16];
int Y[16];

double ARR[16][16];
double COST[16][1 << 16];
int N;

inline double min(double x, double y)
{
    return x < y ? x : y;
}

double dist(int x1, int y1, int x2, int y2)
{
    int dx = x1 - x2;
    int dy = y1 - y2;

    return sqrt(dx * dx + dy * dy);
}

double traverse(int node, int visited)
{
    if (visited == (1 << N) - 1)
    {
        return COST[node][visited] = ARR[0][node];
    }

    if (COST[node][visited] != INF)
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
        std::cin >> X[i] >> Y[i];
    }

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < 1 << N; ++j)
        {
            COST[i][j] = INF;
        }

        for (int j = 0; j < N; ++j)
        {
            ARR[i][j] = dist(X[i], Y[i], X[j], Y[j]);
        }
    }

    std::cout << std::fixed << std::setprecision(6) << traverse(0, 1);

    return 0;
}