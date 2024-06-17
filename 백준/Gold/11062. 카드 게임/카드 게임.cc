#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int UNINIT = 0x7FFFFFFF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int S[1010];
int ARR[1010];
int DP[1010][1010];
int N;

void init()
{
    for (int i = 1; i <= N; ++i)
    {
        S[i] = 0;
        for (int j = 1; j <= N; ++j)
        {
            DP[i][j] = UNINIT;
        }
    }
}

int sol(int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        return ARR[idx0];
    }

    if (DP[idx0][idx1] != UNINIT)
    {
        return DP[idx0][idx1];
    }

    int left = sol(idx0 + 1, idx1);
    int right = sol(idx0, idx1 - 1);
    if (left < right)
    {
        DP[idx0][idx1] = S[idx1] - S[idx0 - 1] - left;
    }
    else
    {
        DP[idx0][idx1] = S[idx1] - S[idx0 - 1] - right;
    }

    return DP[idx0][idx1];
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N;
        init();
        for (int i = 1; i <= N; ++i)
        {
            std::cin >> ARR[i];
            S[i] = S[i - 1] + ARR[i];
        }
        std::cout << sol(1, N) << '\n';
    }

    return 0;
}
