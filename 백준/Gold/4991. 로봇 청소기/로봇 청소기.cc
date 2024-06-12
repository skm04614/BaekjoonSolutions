#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

constexpr int INF = 0x1FFFFFFF;
constexpr char CLEAN = '.';
constexpr char INVALID = 'x';
constexpr char START = 'o';

int MAP[30][30];
int Y, X;

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
        else if (opt == 1)
        {
            return { y + 1, x };
        }
        else if (opt == 2)
        {
            return { y, x - 1 };
        }
        else
        {
            return { y, x + 1 };
        }
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || x < 0 || y >= Y || x >= X;
    }
};

Coords LOC[11];
int DIST[11][11];
int COST[1 << 11][11];
int N;

int VISITED[30][30];
Coords Q[1010];
int LP;
int RP;

void reset_visit()
{
    LP = RP = -1;

    for (int y = 0; y < Y; ++y)
    {
        for (int x = 0; x < X; ++x)
        {
            VISITED[y][x] = 0;
        }
    }
}

bool fill_dist()
{
    for (int i = 0; i < N; ++i)
    {
        reset_visit();

        const Coords& start = LOC[i];
        Q[++RP] = start;
        VISITED[start.y][start.x] = 1;

        while (RP > LP)
        {
            const Coords c = Q[++LP];

            for (int i = 0; i < 4; ++i)
            {
                const Coords n = c.move(i);
                if (n.is_out_of_bounds() || MAP[n.y][n.x] == -1 || VISITED[n.y][n.x])
                {
                    continue;
                }

                Q[++RP] = n;
                VISITED[n.y][n.x] = VISITED[c.y][c.x] + 1;
            }
        }

        for (int j = 0; j < N; ++j)
        {
            const Coords& end = LOC[j];
            if (!VISITED[end.y][end.x])
            {
                return false;
            }

            DIST[i][j] = DIST[j][i] = VISITED[end.y][end.x] - 1;
        }
    }

    return true;
}

int traverse_cost(int node, int visited)
{
    if (visited == (1 << N) - 1)
    {
        return COST[visited][node] = 0;
    }

    if (COST[visited][node] != INF)
    {
        return COST[visited][node];
    }

    for (int v = 1; v < N; ++v)
    {
        if (visited & (1 << v))
        {
            continue;
        }

        COST[visited][node] = min(COST[visited][node], traverse_cost(v, visited | (1 << v)) + DIST[node][v]);
    }

    return COST[visited][node];
}


void init()
{
    for (int i = 0; i <= 10; ++i)
    {
        for (int v = 0; v < (1 << 11); ++v)
        {
            COST[v][i] = INF;
        }

        for (int j = 0; j <= 10; ++j)
        {
            DIST[i][j] = 0;
        }
    }
    N = 0;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (;;)
    {
        std::cin >> X >> Y;
        if (Y == 0 && X == 0)
        {
            break;
        }

        init();

        for (int y = 0; y < Y; ++y)
        {
            for (int x = 0; x < X; ++x)
            {
                char c;
                std::cin >> c;
                if (c == CLEAN)
                {
                    MAP[y][x] = 0;
                }
                else if (c == INVALID)
                {
                    MAP[y][x] = -1;
                }
                else if (c == START)
                {
                    MAP[y][x] = 1;
                    LOC[0] = { y, x };
                }
                else
                {
                    MAP[y][x] = 2;
                    LOC[++N] = { y, x };
                }
            }
        }
        ++N;

        std::cout << (fill_dist() ? traverse_cost(0, 1) : -1) << '\n';
    }

    return 0;
}
