#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int min(int x, int y)
{
    return x < y ? x : y;
}

struct Coords
{
    int y;
    int x;

    bool is_out_of_bounds() const
    {
        return y < 0 || y >= 10 || x < 0 || x >= 10;
    }

    Coords move(int opt) const
    {
        if (opt == 0)
        {
            return { y + 1, x };
        }

        if (opt == 1)
        {
            return { y - 1, x };
        }

        if (opt == 2)
        {
            return { y, x + 1 };
        }

        return { y, x - 1 };
    }
};

int MAP[1 << 10][11];
int K;

int toggle(int *map, const Coords& c)
{
    int cnt = 1;
    int on = (map[c.y] & (1 << c.x)) > 0;
    map[c.y] ^= (1 << c.x);

    for (int i = 0; i < 4; ++i)
    {
        const Coords n = c.move(i);
        if (n.is_out_of_bounds())
        {
            continue;
        }

        ++cnt;
        on += (map[n.y] & (1 << n.x)) > 0;
        map[n.y] ^= (1 << n.x);
    }

    return 2 * on - cnt;
}

int dfs(int* map, int k, int cnt, int y)
{
    if (k == 0)
    {
        return cnt;
    }

    if (y > 10)
    {
        return INF;
    }

    for (int x = 0; x < 10; ++x)
    {
        if (map[y - 1] & (1 << x))
        {
            k -= toggle(map, { y, x });
            ++cnt;
        }
    }

    return dfs(map, k, cnt, y + 1);
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int i = 0; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            char c;
            std::cin >> c;

            K += (c == 'O');
            MAP[0][i] |= ((c == 'O') << j);
            for (int k = 1; k < 1 << 10; ++k)
            {
                MAP[k][i] = MAP[0][i];
            }
        }
    }

    int res = INF;
    for (int _x = 0; _x < (1 << 10); ++_x)
    {
        int cnt = 0;
        int k = K;
        for (int x = 0; x < 10; ++x)
        {
            if (_x & (1 << x))
            {
                k -= toggle(MAP[_x], {0, x});
                ++cnt;
            }
        }

        res = min(res, dfs(MAP[_x], k, cnt, 1));
    }
    std::cout << (res == INF ? -1 : res);

    return 0;
}
