#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}
bool ORIG[10010][510];
bool VISITED[10010][510];
int Y, X;

struct Coords
{
    int y;
    int x;

    Coords move(bool mode, int opt) const
    {
        if (opt == 0)
        {
            return mode ? Coords{ y - 1, x + 1 } : Coords{y + 1, x + 1};
        }

        if (opt == 1)
        {
            return { y, x + 1 };
        }

        return mode ? Coords{ y + 1, x + 1 } : Coords{ y - 1, x + 1 };
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || y >= Y;
    }

    bool reached_end() const
    {
        return x == X - 1;
    }
};

void init()
{
    for (int y = 0; y < Y; ++y)
    {
        for (int x = 0; x < X; ++x)
        {
            VISITED[y][x] = ORIG[y][x];
        }
    }
}

bool dfs(Coords c, bool mode)
{
    VISITED[c.y][c.x] = true;
    if (c.reached_end())
    {
        return true;
    }

    for (int i = 0; i < 3; ++i)
    {
        Coords n = c.move(mode, i);
        if (n.is_out_of_bounds() || VISITED[n.y][n.x])
        {
            continue;
        }

        if (dfs(n, mode))
        {
            return true;
        }
    }
    
    return false;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> Y >> X;
    for (int y = 0; y < Y; ++y)
    {
        for (int x = 0; x < X; ++x)
        {
            char c;
            std::cin >> c;
            ORIG[y][x] = c == 'x';
        }
    }

    int res_1 = 0;
    init();
    for (int y = 0; y < Y; ++y)
    {
        res_1 += dfs({ y, 0 }, false);
    }

    int res_2 = 0;
    init();
    for (int y = 0; y < Y; ++y)
    {
        res_2 += dfs({ y, 0 }, true);
    }

    std::cout << max(res_1, res_2);

    return 0;
}
