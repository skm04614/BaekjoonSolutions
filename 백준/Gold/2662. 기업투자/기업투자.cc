#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


int PROFIT[21][301];
int DP[301];
int REC[21][301];

int M;
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M;

    for (int n = 1; n <= N; ++n)
    {
        int val;
        std::cin >> val;
        for (int m = 1; m <= M; ++m)
        {
            std::cin >> PROFIT[m][n];
        }
    }

    for (int m = 1; m <= M; ++m)
    {
        for (int n = N; n >= 1; --n)
        {
            for (int k = 0; k <= n; ++k)
            {
                const int tmp = DP[n - k] + PROFIT[m][k];
                if (tmp > DP[n])
                {
                    DP[n] = tmp;
                    REC[m][n] = k;
                }
            }
        }
    }

    int n = N;
    int cnt[21] = {};
    int sum = 0;
    for (int m = M; m >= 1; --m)
    {
        cnt[m] = REC[m][n];
        n -= cnt[m];
    }

    std::cout << DP[N] << '\n';
    for (int m = 1; m <= M; ++m)
    {
        std::cout << cnt[m] << ' ';
    }

    return 0;
}
