#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ADJ[510][510];
int ARR[510];
int N;

int IN_DEGREE[510];
int Q[510];
int LP;
int RP;

int REC[510];
int R;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void init()
{
    LP = RP = 0;
    R = 0;

    for (int i = 1; i <= N; i++)
    {
        IN_DEGREE[i] = 0;
        for (int j = 1; j <= N; j++)
        {
            ADJ[i][j] = 0;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N;
        for (int i = 1; i <= N; i++)
        {
            std::cin >> ARR[i];
        }

        init();

        for (int i = 1; i <= N; i++)
        {
            for (int j = i + 1; j <= N; j++)
            {
                ADJ[ARR[i]][ARR[j]] = 1;
                ++IN_DEGREE[ARR[j]];
            }
        }

        int M;
        std::cin >> M;
        for (int i = 1; i <= M; i++)
        {
            int v1, v2;
            std::cin >> v1 >> v2;
            swap(ADJ[v1][v2], ADJ[v2][v1]);

            IN_DEGREE[v2] += ADJ[v1][v2] ? 1 : -1;
            IN_DEGREE[v1] += ADJ[v1][v2] ? -1 : 1;
        }

        for (int i = 1; i <= N; i++)
        {
            if (IN_DEGREE[i])
            {
                continue;
            }

            Q[++RP] = i;
        }

        while (RP > LP)
        {
            int v = Q[++LP];
            REC[++R] = v;

            for (int d = 1; d <= N; d++)
            {
                if (ADJ[v][d])
                {
                    --ADJ[v][d];
                    if (--IN_DEGREE[d] == 0)
                    {
                        Q[++RP] = d;
                    }
                }
            }
        }

        if (R == N)
        {
            for (int i = 1; i <= N; i++)
            {
                std::cout << REC[i] << ' ';
            }
        }
        else
        {
            std::cout << "IMPOSSIBLE";
        }
        std::cout << '\n';
    }

    return 0;
}