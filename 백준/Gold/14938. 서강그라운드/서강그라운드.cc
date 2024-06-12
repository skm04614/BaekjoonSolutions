#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int ITEMS[110];
int D[110][110];
int N;
int M;
int R;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M >> R;
    for (register int i = 1; i <= N; i++)
    {
        std::cin >> ITEMS[i];
        for (register int j = 1; j <= N; j++)
        {
            D[i][j] = (i == j) ? 0 : INF;
        }
    }

    for (register int i = 1; i <= R; i++)
    {
        register int src, dest, w;
        std::cin >> src >> dest >> w;
        D[src][dest] = D[dest][src] = w;
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

                D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }

    int sol = 0;
    for (register int i = 1; i <= N; i++)
    {
        int tmp_sol = 0;
        for (register int j = 1; j <= N; j++)
        {
            tmp_sol += ITEMS[j] * (D[i][j] <= M);
        }
        sol = sol > tmp_sol ? sol : tmp_sol;
    }
    std::cout << sol;

    return 0;
}