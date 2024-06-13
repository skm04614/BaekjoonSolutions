#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGM = 30;

int INIT[100100];
int N;

int NEXT[MAX_LOGM + 1][100100];
int LAST[100100];
int M;

int K;


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M >> K;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> INIT[i];
    }

    for (int i = 1; i <= M; ++i)
    {
        std::cin >> NEXT[0][i];
    }

    for (int logm = 1; logm <= MAX_LOGM; ++logm)
    {
        for (int i = 1; i <= M; ++i)
        {
            NEXT[logm][i] = NEXT[logm - 1][NEXT[logm - 1][i]];
        }
    }

    for (int i = 1; i <= M; ++i)
    {
        int k = K - 1;
        int v = i;
        for (int logm = MAX_LOGM; logm >= 0; --logm)
        {
            if (k >= (1 << logm))
            {
                v = NEXT[logm][v];
                k -= (1 << logm);
            }
        }
        LAST[i] = v;
    }

    for (int i = 1; i <= N; ++i)
    {
        std::cout << LAST[INIT[i]] << ' ';
    }

    return 0;
}