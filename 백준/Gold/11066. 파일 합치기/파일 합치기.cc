#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x2FFFFFFF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int ARR[501];
int ACC[501];
int DP[501][501];
int N;

void reset()
{
    ACC[0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            DP[i][j] = INF;
        }
    }
}

int min_cost(int idx0, int idx1)
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
        DP[idx0][idx1] = min(DP[idx0][idx1], min_cost(idx0, i) + min_cost(i + 1, idx1) + ACC[idx1] - ACC[idx0 - 1]);
    }

    return DP[idx0][idx1];
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
        reset();
        for (int i = 1; i <= N; ++i)
        {
            std::cin >> ARR[i];
        }

        ACC[0] = ARR[0];
        for (int i = 1; i <= N; ++i)
        {
            ACC[i] = ACC[i - 1] + ARR[i];
        }

        std::cout << min_cost(1, N) << '\n';
    }


    return 0;
}
