#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int T;

int V[110];
int N[110];
int K;

int DP[110][10010];

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> T >> K;
    for (int i = 1; i <= K; ++i)
    {
        std::cin >> V[i] >> N[i];
    }

    DP[0][0] = 1;
    for (int i = 1; i <= K; ++i)
    {
        int tmp = 0;
        for (int v = 0; v <= T; ++v)
        {
            int tmp = 0;
            for (int n = 0; n <= N[i]; ++n)
            {
                tmp += (v - n * V[i]) >= 0 ? DP[i - 1][v - n * V[i]] : 0;
            }

            DP[i][v] += tmp;
        }
    }

    std::cout << DP[K][T];

    return 0;
}
