#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int D[101][101];
int REC[101][101];
int N;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

void print_record(int src, int dest, int cnt)
{
    if (REC[src][dest] == 0)
    {
        std::cout << cnt << ' ' << src << ' ';
        return;
    }

    print_record(src, REC[src][dest], cnt + 1);

    std::cout << dest << ' ';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    for (register int i = 1; i <= N; i++)
    {
        for (register int j = 1; j <= N; j++)
        {
            D[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (register int i = 1; i <= M; i++)
    {
        int src, dest, w;
        std::cin >> src >> dest >> w;

        if (w < D[src][dest])
        {
            D[src][dest] = w;
            REC[src][dest] = src;
        }
    }

    for (register int k = 1; k <= N; k++)
    {
        for (register int i = 1; i <= N; i++)
        {
            for (register int j = 1; j <= N; j++)
            {
                if (D[i][k] == INF || D[k][j] == INF)
                {
                    continue;
                }

                int d = D[i][k] + D[k][j];
                if (d < D[i][j])
                {
                    D[i][j] = d;
                    REC[i][j] = REC[k][j];
                }
            }
        }
    }

    for (register int i = 1; i <= N; i++)
    {
        for (register int j = 1; j <= N; j++)
        {
            std::cout << (D[i][j] == INF ? 0 : D[i][j]) << ' ';
        }
        std::cout << '\n';
    }

    for (register int i = 1; i <= N; i++)
    {
        for (register int j = 1; j <= N; j++)
        {
            if (D[i][j] == INF || D[i][j] == 0)
            {
                std::cout << 0;
            }
            else
            {
                print_record(i, j, 1);
            }
            std::cout << '\n';
        }
    }

    return 0;
}