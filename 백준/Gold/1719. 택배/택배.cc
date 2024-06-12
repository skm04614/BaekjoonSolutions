#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int D[210][210];
int S[210][210];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            D[i][j] = (i == j) ? 0 : INF;
            S[i][j] = 0;
        }
    }

    for (int i = 1; i <= M; i++)
    {
        int src, dest, w;
        std::cin >> src >> dest >> w;

        D[dest][src] = D[src][dest] = w;
        S[dest][src] = src;
        S[src][dest] = dest;
    }

    for (int k = 1; k <= N; k++)
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                if (D[i][k] == INF || D[k][j] == INF)
                {
                    continue;
                }

                if (D[i][k] + D[k][j] < D[i][j])
                {
                    S[i][j] = S[i][k];
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N; j++)
        {
            if (S[i][j])
            {
                std::cout << S[i][j] << ' ';
            }
            else
            {
                std::cout << "- ";
            }
        }
        std::cout << '\n';
    }

    return 0;
}