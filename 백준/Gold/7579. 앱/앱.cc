#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int MEM[110];
int C[110];
int N;
int M;

int DP[10100];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> MEM[i];
    }
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> C[i];
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int c = 10000; c >= C[i]; --c)
        {
            DP[c] = max(DP[c - C[i]] + MEM[i], DP[c]);
        }
    }

    for (int c = 0; c <= 10000; ++c)
    {
        if (DP[c] >= M)
        {
            std::cout << c;
            break;
        }
    }

    return 0;
}
