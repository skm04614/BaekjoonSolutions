#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int N, T;
int DP[2][10010];

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> T;
    
    int p = 0;
    int c = 1;
    for (int i = 0; i < N; i++)
    {
        int cost, s;
        std::cin >> cost >> s;

        for (int t = 0; t < cost; t++)
        {
            DP[c][t] = DP[p][t];
        }

        DP[c][cost] = max(DP[p][cost], s);

        for (int t = cost + 1; t <= 10000; t++)
        {
            DP[c][t] = DP[p][t];
            if (DP[p][t - cost])
            {
                DP[c][t] = max(DP[c][t], DP[p][t - cost] + s);
            }
        }

        p ^= 1;
        c ^= 1;
    }

    int sol = 0;
    for (int t = 0; t <= T; t++)
    {
        sol = sol > DP[p][t] ? sol : DP[p][t];
    }
    std::cout << sol;


    return 0;
}