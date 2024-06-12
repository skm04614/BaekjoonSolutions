#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[1001][1001];
int GROUP[1001][1001];

int GROUP_SIZE[1000001];
int GROUP_VISITED[1000001];
int GIDX = 0;
int N, M;

struct Coords
{
    int y;
    int x;

    Coords move(int opt) const
    {
        switch (opt)
        {
        case 0:
            return { y + 1, x };
        case 1:
            return { y, x + 1 };
        case 2:
            return { y - 1, x };
        default:
            return { y, x - 1 };
        }
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || x < 0 || y >= N || x >= M;
    }
};

Coords Q[1000001];
int LP;
int RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);
    
    std::cin >> N >> M;
    char c;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            std::cin >> c;
            MAP[i][j] = (c == '1');
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            if (MAP[i][j] == 1 || GROUP[i][j] != 0)
            {
                continue;
            }

            LP = -1;
            RP = -1;
            GIDX++;

            Q[++RP] = { i, j };
            GROUP[i][j] = GIDX;
            GROUP_SIZE[GIDX]++;

            while (RP > LP)
            {
                const Coords& current = Q[++LP];

                for (int i = 0; i < 4; i++)
                {
                    const Coords next = current.move(i);

                    if (next.is_out_of_bounds())
                    {
                        continue;
                    }

                    if (MAP[next.y][next.x] == 1 || GROUP[next.y][next.x] != 0)
                    {
                        continue;
                    }

                    Q[++RP] = next;
                    GROUP[next.y][next.x] = GIDX;
                    GROUP_SIZE[GIDX]++;
                }
            }
        }
    }

    int tag = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            tag++;

            if (MAP[i][j] == 0)
            {
                std::cout << 0;
            }
            else
            {
                int val = 1;
                const Coords current = { i, j };
                for (int k = 0; k < 4; k++)
                {
                    const Coords next = current.move(k);
                    if (next.is_out_of_bounds())
                    {
                        continue;
                    }

                    int gidx = GROUP[next.y][next.x];
                    if (GROUP_VISITED[gidx] == tag)
                    {
                        continue;
                    }

                    GROUP_VISITED[gidx] = tag;
                    val = (val + GROUP_SIZE[gidx]) % 10;
                }
                std::cout << val;
            }
        }
        std::cout << '\n';
    }


    return 0;
}