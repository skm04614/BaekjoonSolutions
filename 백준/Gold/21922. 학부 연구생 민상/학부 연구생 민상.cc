#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

enum
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
};

int MAP[2020][2020];
bool VISITED[4][2020][2020];
int N, M;

struct Coords
{
    int y;
    int x;
    int dir;

    Coords traverse(int mode) const
    {
        if (mode == 0 || mode == 9)
        {
            return move(dir);
        }

        if (mode == 1)
        {
            if (dir == LEFT || dir == RIGHT)
            {
                return move((dir + 2) % 4);
            }

            return move(dir);
        }

        if (mode == 2)
        {
            if (dir == UP || dir == DOWN)
            {
                return move((dir + 2) % 4);
            }

            return move(dir);
        }

        if (mode == 3)
        {
            if (dir == UP)
            {
                return move(RIGHT);
            }

            if (dir == LEFT)
            {
                return move(DOWN);
            }

            if (dir == RIGHT)
            {
                return move(UP);
            }

            return move(LEFT);
        }

        if (mode == 4)
        {
            if (dir == UP)
            {
                return move(LEFT);
            }

            if (dir == LEFT)
            {
                return move(UP);
            }

            if (dir == RIGHT)
            {
                return move(DOWN);
            }

            return move(RIGHT);
        }
    }

    Coords move(int dir) const
    {
        if (dir == UP)
        {
            return { y - 1, x, dir };
        }

        if (dir == RIGHT)
        {
            return { y, x + 1, dir };
        }

        if (dir == DOWN)
        {
            return { y + 1, x, dir };
        }

        return { y, x - 1, dir };
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || y >= N || x < 0 || x >= M;
    }
};

Coords Q[4 * 2020 * 2020];
int RP;
int LP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            std::cin >> MAP[i][j];
            if (MAP[i][j] == 9)
            {
                for (int dir = 0; dir < 4; ++dir)
                {
                    Q[++RP] = { i, j, dir };
                    VISITED[dir][i][j] = true;
                }
            }
        }
    }

    while (RP > LP)
    {
        const Coords& c = Q[++LP];

        const Coords n = c.traverse(MAP[c.y][c.x]);
        if (n.is_out_of_bounds() || VISITED[n.dir][n.y][n.x])
        {
            continue;
        }

        Q[++RP] = n;
        VISITED[n.dir][n.y][n.x] = true;
    }

    int cnt = 0;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < M; ++j)
        {
            int tmp = 0;
            for (int dir = 0; dir < 4; ++dir)
            {
                tmp |= VISITED[dir][i][j];
            }
            cnt += tmp;
        }
    }
    std::cout << cnt;
    
    return 0;
}
