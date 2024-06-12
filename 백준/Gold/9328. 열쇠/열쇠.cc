#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int EMPTY = 0;
constexpr int BLOCKED = 1 << 29;
constexpr int TREASURE = 1 << 30;
constexpr int SIZE = 10100;

int MAP[110][110];
int N, M;

int ctoi(char c)
{
    if ('a' <= c && c <= 'z')
    {
        return 1 << (c - 'a');
    }

    if ('A' <= c && c <= 'Z')
    {
        return -(1 << (c - 'A'));
    }

    return 0;
}

struct Coords
{
    int y;
    int x;
    
    Coords move(int opt) const
    {
        if (opt == 0)
        {
            return { y - 1, x };
        }

        if (opt == 1)
        {
            return { y + 1, x };
        }

        if (opt == 2)
        {
            return { y, x - 1 };
        }

        return { y, x + 1 };
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || y >= N || x < 0 || x >= M;
    }

    int id() const
    {
        return 100 * y + x;
    }
};

Coords Q[SIZE];
bool VISITED[SIZE];
int LP, RP;

void treat_boundary(int& key, int& treasure_count)
{
    for (int y = 0; y < N; ++y)
    {
        if (MAP[y][0] == TREASURE)
        {
            ++treasure_count;
            MAP[y][0] = EMPTY;
        }
        else if (MAP[y][0] > 0 && MAP[y][0] != BLOCKED)
        {
            key |= MAP[y][0];
            MAP[y][0] = EMPTY;
        }

        if (MAP[y][M - 1] == TREASURE)
        {
            ++treasure_count;
            MAP[y][M - 1] = EMPTY;
        }
        else if (MAP[y][M - 1] > 0 && MAP[y][M - 1] != BLOCKED)
        {
            key |= MAP[y][M - 1];
            MAP[y][M - 1] = EMPTY;
        }
    }

    for (int x = 0; x < M; ++x)
    {
        if (MAP[0][x] == TREASURE)
        {
            ++treasure_count;
            MAP[0][x] = EMPTY;
        }
        else if (MAP[0][x] > 0 && MAP[0][x] != BLOCKED)
        {
            key |= MAP[0][x];
            MAP[0][x] = EMPTY;
        }

        if (MAP[N - 1][x] == TREASURE)
        {
            ++treasure_count;
            MAP[N - 1][x] = EMPTY;
        }
        else if (MAP[N - 1][x] > 0 && MAP[N - 1][x] != BLOCKED)
        {
            key |= MAP[N - 1][x];
            MAP[N - 1][x] = EMPTY;
        }
    }
}

void init_settings(int key)
{
    for (int i = 0; i < SIZE; ++i)
    {
        VISITED[i] = false;
    }

    LP = RP = 0;
    for (int y = 0; y < N; ++y)
    {
        if (MAP[y][0] == EMPTY || (MAP[y][0] < 0 && (-MAP[y][0] & key)))
        {
            Q[++RP] = { y, 0 };
            VISITED[Q[RP].id()] = true;
        }

        if (MAP[y][M - 1] == EMPTY || (MAP[y][M - 1] < 0 && (-MAP[y][M - 1] & key)))
        {
            Q[++RP] = { y, M - 1 };
            VISITED[Q[RP].id()] = true;
        }
    }

    for (int x = 0; x < M; ++x)
    {
        if (MAP[0][x] == EMPTY || (MAP[0][x] < 0 && (-MAP[0][x] & key)))
        {
            Q[++RP] = { 0, x };
            VISITED[Q[RP].id()] = true;
        }

        if (MAP[N - 1][x] == EMPTY || (MAP[N - 1][x] < 0 && (-MAP[N - 1][x] & key)))
        {
            Q[++RP] = { N - 1, x };
            VISITED[Q[RP].id()] = true;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N >> M;

        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < M; ++j)
            {
                char c;
                std::cin >> c;
                if (c == '*')
                {
                    MAP[i][j] = BLOCKED;
                }
                else if (c == '.')
                {
                    MAP[i][j] = EMPTY;
                }
                else if (c == '$')
                {
                    MAP[i][j] = TREASURE;
                }
                else
                {
                    MAP[i][j] = ctoi(c);
                }
            }
        }

        char buf[30] = "";
        std::cin >> buf;
        int key = 0;
        for (int i = 0; buf[i]; ++i)
        {
            key |= ctoi(buf[i]);
        }

        /* -- bfs -- */
        int last_key = 0;
        int current_key = key;
        int res = 0;

        treat_boundary(current_key, res);

        for (;;)
        {
            last_key = current_key;

            init_settings(current_key);

            while (RP > LP)
            {
                const Coords& c = Q[++LP % SIZE];

                for (int i = 0; i < 4; ++i)
                {
                    const Coords n = c.move(i);
                    if (n.is_out_of_bounds() || MAP[n.y][n.x] == BLOCKED || VISITED[n.id()])
                    {
                        continue;
                    }

                    if (MAP[n.y][n.x] < 0)
                    {
                        if (!(-MAP[n.y][n.x] & current_key))
                        {
                            continue;
                        }

                        MAP[n.y][n.x] = EMPTY;
                    }

                    if (MAP[n.y][n.x] == TREASURE)
                    {
                        ++res;
                        MAP[n.y][n.x] = EMPTY;
                    }

                    if (MAP[n.y][n.x] != EMPTY)
                    {
                        current_key |= MAP[n.y][n.x];
                        MAP[n.y][n.x] = EMPTY;
                    }

                    VISITED[n.id()] = true;
                    Q[++RP % SIZE] = n;
                }
            }

            if (current_key == last_key)
            {
                break;
            }
        }
        std::cout << res << '\n';
    }

    return 0;
}
