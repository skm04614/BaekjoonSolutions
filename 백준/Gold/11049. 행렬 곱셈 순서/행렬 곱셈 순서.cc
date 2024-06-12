#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull INF = 0x2FFFFFFFFFFFFFFF;

inline ull min(ull x, ull y)
{
    return x < y ? x : y;
}

struct Dimension
{
    int a;
    int b;
};

Dimension ARR[501];
ull DP[501][501];
int N;


void init()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            DP[i][j] = INF;
        }
    }
}

ull min_cost(int idx0, int idx1)
{
    if (DP[idx0][idx1] != INF)
    {
        return DP[idx0][idx1];
    }

    if (idx0 == idx1)
    {
        return DP[idx0][idx0] = 0;
    }

    for (int i = idx0; i < idx1; ++i)
    {
        DP[idx0][idx1] = min(DP[idx0][idx1], min_cost(idx0, i) + min_cost(i + 1, idx1) + ARR[idx0].a * ARR[i].b * ARR[idx1].b);
    }

    return DP[idx0][idx1];
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;

    init();

    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i].a >> ARR[i].b;
    }

    std::cout << min_cost(1, N);

    return 0;
}
