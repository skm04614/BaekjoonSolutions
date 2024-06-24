#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr char UNK = '#';
constexpr char MINE = '*';
constexpr char EMPTY = ' ';

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

char MAP[110][110];
int N;

struct Coords
{
    int y;
    int x;

    Coords move(int opt) const
    {
        switch (opt)
        {
        case 0:
            return { y, x - 1 };
        case 1:
            return { y, x + 1 };
        case 2:
            return { y - 1, x - 1 };
        case 3:
            return { y - 1, x + 1 };
        case 4:
            return { y + 1, x - 1 };
        case 5:
            return { y + 1, x + 1 };
        case 6:
            return { y - 1, x };
        default:
            return { y + 1, x };
        }
    }

    bool is_out_of_bounds() const
    {
        return y <= 0 || (y >= N - 1) || x <= 0 || (x >= N - 1);
    }

    bool is_boundary() const
    {
        return y == 0 || y == N - 1 || x == 0 || x == N - 1;
    }

    int count(char target) const
    {
        int cnt = 0;
        for (int i = 0; i < 8; ++i)
        {
            const Coords n = move(i);
            if (n.is_out_of_bounds())
            {
                continue;
            }

            cnt += (MAP[n.y][n.x] == target);
        }
        return cnt;
    }

    int id() const
    {
        return y * 100 + x;
    }
};

Coords POOL[500];
int P;

bool VISITED[110][110];

bool is_num(char c)
{
    return '0' <= c && c <= '9';
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> MAP[i];
        for (int j = 0; j < N; ++j)
        {
            if (is_num(MAP[i][j]))
            {
                POOL[++P] = { i, j };
            }
        }
    }

    int k = 0;
    while (k < (4 * (N - 1)))
    {
        for (int p = 1; p <= P; ++p)
        {
            const Coords& c = POOL[p];
            if (VISITED[c.y][c.x])
            {
                continue;
            }

            const int val = MAP[c.y][c.x] - '0';
            if (val == 0 || c.count(UNK) == val)
            {
                for (int i = 0; i < 8; ++i)
                {
                    const Coords n = c.move(i);
                    if (!n.is_out_of_bounds() && MAP[n.y][n.x] == UNK)
                    {
                        if (val == 0)
                        {
                            MAP[n.y][n.x] = EMPTY;
                        }
                        else
                        {
                            MAP[n.y][n.x] = MINE;
                            for (int i = 0; i < 8; ++i)
                            {
                                const Coords b = n.move(i);
                                if (b.is_boundary())
                                {
                                    --MAP[b.y][b.x];
                                }
                            }
                        }
                    }
                }

                ++k;
                VISITED[c.y][c.x] = true;
            }
        }
    }

    int sol = 0;
    for (int i = 1; i < N - 1; ++i)
    {
        for (int j = 1; j < N - 1; ++j)
        {
            sol += MAP[i][j] != EMPTY;
        }
    }
    std::cout << sol;
    
    return 0;
}
