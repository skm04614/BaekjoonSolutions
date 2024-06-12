#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int REC[31][210][210];
int MAP[210][210];
int X, Y, K;

struct Coords
{
    int k;
    int y;
    int x;

    bool is_out_of_bounds() const
    {
        return y < 1 || y > Y || x < 1 || x > X || k < 0;
    }

    Coords move(int op) const
    {
        switch (op)
        {
        case 0:
            return { k, y, x + 1 };
        case 1:
            return { k, y, x - 1 };
        case 2:
            return { k, y + 1, x };
        default:
            return { k, y - 1, x };
        }
    }

    Coords special_move(int op) const
    {
        switch (op)
        {
        case 0:
            return { k - 1, y + 2, x + 1 };
        case 1:
            return { k - 1, y + 2, x - 1 };
        case 2:
            return { k - 1, y - 2, x + 1 };
        case 3:
            return { k - 1, y - 2, x - 1 };
        case 4:
            return { k - 1, y + 1, x + 2 };
        case 5:
            return { k - 1, y - 1, x + 2 };
        case 6:
            return { k - 1, y + 1, x - 2 };
        default:
            return { k - 1, y - 1, x - 2 };
        }
    }
};

Coords Q[31 * 210 * 210];
int LP, RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> K >> X >> Y;
    for (int i = 1; i <= Y; ++i)
    {
        for (int j = 1; j <= X; ++j)
        {
            std::cin >> MAP[i][j];
        }
    }

    REC[K][1][1] = 1;
    Q[++RP] = { K, 1, 1 };
    while (RP > LP)
    {
        const Coords c = Q[++LP];
        for (int i = 0; i < 4; ++i)
        {
            const Coords n = c.move(i);
            if (n.is_out_of_bounds() || REC[n.k][n.y][n.x] || MAP[n.y][n.x])
            {
                continue;
            }

            REC[n.k][n.y][n.x] = REC[c.k][c.y][c.x] + 1;
            Q[++RP] = n;
        }

        if (c.k == 0)
        {
            continue;
        }

        for (int i = 0; i < 8; ++i)
        {
            const Coords n = c.special_move(i);
            if (n.is_out_of_bounds() || REC[n.k][n.y][n.x] || MAP[n.y][n.x])
            {
                continue;
            }

            REC[n.k][n.y][n.x] = REC[c.k][c.y][c.x] + 1;
            Q[++RP] = n;
        }
    }

    int res = 0x7FFFFFFF;
    for (int k = 0; k <= K; ++k)
    {
        if (REC[k][Y][X] == 0)
        {
            continue;
        }

        res = min(res, REC[k][Y][X] - 1);
    }
    std::cout << (res == 0x7FFFFFFF ? -1 : res);

    return 0;
}
