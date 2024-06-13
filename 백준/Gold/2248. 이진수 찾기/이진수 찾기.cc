#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

unsigned int DP[2][32][32];
int N;
int L;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    unsigned int k;
    std::cin >> N >> L >> k;

    DP[0][1][0] = DP[1][1][1] = 1;
    for (int n = 2; n <= N; ++n)
    {
        DP[0][n][0] = DP[0][n - 1][0] + DP[1][n - 1][0];
        for (int l = 1; l <= L; ++l)
        {
            DP[0][n][l] = DP[0][n - 1][l] + DP[1][n - 1][l];
            DP[1][n][l] = DP[0][n - 1][l - 1] + DP[1][n - 1][l - 1];
        }
    }

    for (int n = N; n >= 1; --n)
    {
        unsigned int sum = 0;
        for (int l = 0; l <= L; ++l)
        {
            sum += DP[0][n][l];
        }

        if (k > sum)
        {
            k -= sum;
            --L;
            std::cout << 1;
        }
        else
        {
            std::cout << 0;
        }
    }

    return 0;
}
