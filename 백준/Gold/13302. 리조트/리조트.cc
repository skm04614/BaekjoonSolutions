#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int DP[110][110];
int ARR[110];
int N;
int M;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

void init()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int token = 0; token <= 100; ++token)
        {
            DP[token][i] = INF;
        }
    }
}

int sol(int d, int token)
{
    if (d > N)
    {
        return DP[token][d] = 0;
    }

    if (ARR[d])
    {
        return sol(d + 1, token);
    }

    if (DP[token][d] != INF)
    {
        return DP[token][d];
    }

    
    DP[token][d] = min(sol(d + 3, token + 1) + 25000, sol(d + 5, token + 2) + 37000);
    DP[token][d] = min(DP[token][d], sol(d + 1, token) + 10000);
    if (token >= 3)
    {
        DP[token][d] = min(DP[token][d], sol(d + 1, token - 3));
    }

    return DP[token][d];
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M;
    for (int i = 1; i <= M; ++i)
    {
        int d;
        std::cin >> d;
        ARR[d] = 1;
    }

    init();
    std::cout << sol(1, 0);

    return 0;
}
