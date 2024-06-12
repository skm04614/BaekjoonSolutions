#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int ARR[100100];
int N;

int DP[2][100100];

inline int max(int n, int m)
{
    return n > m ? n : m;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    int sol = -0x7FFFFFFF;
    DP[0][0] = DP[1][0] = -0x7FFFFFFF;
    for (int i = 1; i <= N; i++)
    {
        DP[0][i] = DP[0][i - 1] < 0 ? ARR[i] : DP[0][i - 1] + ARR[i];

        DP[1][i] = DP[1][i - 1] < 0 ? ARR[i] : DP[1][i - 1] + ARR[i];
        DP[1][i] = max(DP[1][i], DP[0][i - 1]);

        sol = max(sol, DP[0][i]);
        sol = max(sol, DP[1][i]);
    }
    std::cout << sol;

    return 0;
}