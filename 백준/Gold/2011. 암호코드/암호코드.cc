#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 1000000;

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { len++; }
    return len;
}

char BUF[5050];
int B;

int DP[5050][27];
int DP_SUM[5050];

void sol(void)
{
    DP_SUM[0] = 1;
    for (int i = 0; i < B; ++i)
    {
        const char c = BUF[i];
        const int j = i + 1;
        const int n = c - '0';

        if (n == 0 && DP[j - 1][1] == 0 && DP[j - 1][2] == 0)
        {
            std::cout << 0;
            return;
        }

        if (n != 0)
        {
            DP[j][n] = DP_SUM[j - 1];
        }

        DP[j][10 + n] = DP[j - 1][1];
        if (n <= 6)
        {
            DP[j][20 + n] = DP[j - 1][2];
        }

        for (int k = 1; k <= 26; ++k)
        {
            DP_SUM[j] = (DP_SUM[j] + DP[j][k]) % MOD;
        }
    }

    std::cout << DP_SUM[B];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;
    B = _slen(BUF);

    sol();


    return 0;
}