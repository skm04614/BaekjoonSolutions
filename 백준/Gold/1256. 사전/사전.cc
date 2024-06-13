#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr int A = 0;
constexpr int Z = 1;
constexpr ull MAX_K = 1'000'000'000;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

ull DP[2][201][101];
int N, M, L;
ull K;

void sol()
{
    if (DP[0][L][M] + DP[1][L][M] < K)
    {
        std::cout << -1;
        return;
    }

    for (int l = L; l >= 1; --l)
    {
        if (K > DP[A][l][M])
        {
            K -= DP[A][l][M];
            --M;
            std::cout << 'z';
        }
        else
        {
            --N;
            std::cout << 'a';
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M >> K;
    L = N + M;

    int len = 1;
    DP[0][1][0] = DP[1][1][1] = 1;
    for (len = 2; len <= L; ++len)
    {
        for (int m = max(0, len - N); m <= M; ++m)
        {
            if (m == 0)
            {
                DP[A][len][0] = DP[A][len - 1][0] + DP[Z][len - 1][0];
                continue;
            }

            DP[A][len][m] = DP[A][len - 1][m] + DP[Z][len - 1][m];
            DP[Z][len][m] = DP[A][len - 1][m - 1] + DP[Z][len - 1][m - 1];
        }
    }

    sol();

    return 0;
}
