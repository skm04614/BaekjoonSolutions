#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[1010][1010];
int RECORD[2][12][1010][1010];
int N, M, K;

struct Coords
{
    int y;
    int x;
    int k;
    bool morning;

    Coords move(int opt) const
    {
        switch (opt)
        {
        case 0:
            return { y + 1, x, k, !morning };
        case 1:
            return { y - 1, x, k, !morning };
        case 2:
            return { y, x + 1, k, !morning };
        default:
            return { y, x - 1, k, !morning };
        }
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || x < 0 || y >= N || x >= M;
    }
};

Coords Q[24002000];
int LP;
int RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M >> K;
    char c;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cin >> c;
            MAP[i][j] = (c == '1');
        }
    }

    LP = RP = -1;
    Q[++RP] = { 0, 0, K, true };
    RECORD[1][K][0][0] = 1;

    while (RP > LP)
    {
        const Coords& current = Q[++LP];
        const int& record = RECORD[current.morning][current.k][current.y][current.x];

        for (int i = 0; i < 4; i++)
        {
            Coords next = current.move(i);

            if (next.is_out_of_bounds())
            {
                continue;
            }

            if (MAP[next.y][next.x])
            {
                if (current.morning == false)
                {
                    next = { current.y, current.x, current.k, !current.morning };
                }
                else
                {
                    next.k--;
                    if (next.k < 0)
                    {
                        continue;
                    }
                }
            }

            if (RECORD[next.morning][next.k][next.y][next.x])
            {
                continue;
            }

            RECORD[next.morning][next.k][next.y][next.x] = record + 1;
            Q[++RP] = next;
        }
    }

    int sol = 0x7FFFFFFF;
    for (int k = 0; k <= K; k++)
    {
        for (int morning = 0; morning < 2; morning++)
        {
            if (RECORD[morning][k][N - 1][M - 1] == 0)
            {
                continue;
            }

            sol = sol < RECORD[morning][k][N - 1][M - 1] ? sol : RECORD[morning][k][N - 1][M - 1];
        }
    }

    std::cout << (sol == 0x7FFFFFFF ? -1 : sol);

    return 0;
}