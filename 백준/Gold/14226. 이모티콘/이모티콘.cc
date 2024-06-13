#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int SIZE = 2020;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

struct Element
{
    int x;
    int c;

    Element move(int opt) const
    {
        if (opt == 0)
        {
            return { x + c, c };
        }

        if (opt == 1)
        {
            return { x, x };
        }

        return { x - 1, c };
    }

    bool is_out_of_bounds() const
    {
        return x < 0 || x >= SIZE || c < 0 || c >= SIZE;
    }
};

int VISITED[SIZE][SIZE];
Element Q[SIZE * SIZE];
int LP;
int RP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    VISITED[1][0] = 1;
    Q[++RP] = { 1, 0 };
    while (RP > LP)
    {
        const Element& c = Q[++LP];
        for (int i = 0; i < 3; ++i)
        {
            const Element n = c.move(i);
            if (n.is_out_of_bounds() || VISITED[n.x][n.c])
            {
                continue;
            }

            VISITED[n.x][n.c] = VISITED[c.x][c.c] + 1;
            Q[++RP] = n;
        }
    }

    int n;
    std::cin >> n;

    int res = 0x7FFFFFFF;
    for (int i = 0; i < SIZE; ++i)
    {
        if (VISITED[n][i] == 0)
        {
            continue;
        }

        res = min(res, VISITED[n][i]);
    }
    std::cout << res - 1;

    return 0;
}
