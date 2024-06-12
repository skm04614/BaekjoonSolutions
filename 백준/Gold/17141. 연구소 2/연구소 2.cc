#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

constexpr int EMPTY = 0;
constexpr int WALL = 1;
constexpr int VIRUS = 2;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int REC[51][51];
int MAP[51][51];
int N;
int M;
int T;

struct Coords
{
    int y;
    int x;

    Coords move(int opt) const
    {
        if (opt == 0)
        {
            return { y + 1, x };
        }
        else if (opt == 1)
        {
            return { y, x + 1 };
        }
        else if (opt == 2)
        {
            return { y - 1, x };
        }
        else
        {
            return { y, x - 1 };
        }
    }

    bool is_invalid() const
    {
        return y < 0 || x < 0 || y >= N || x >= N || MAP[y][x] == WALL;
    }
};

Coords V_LOC[11];
int V;

Coords Q[2550];
int LP;
int RP;

void reset()
{
    LP = RP = -1;

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            REC[i][j] = 0;
        }
    }
}

int run(int sidx, int cnt, int selected)
{
    if (cnt == M)
    {
        reset();

        for (int i = 0; i < V; ++i)
        {
            const Coords& v = V_LOC[i];

            if (selected & (1 << i))
            {
                REC[v.y][v.x] = 1;
                Q[++RP] = v;
            }
        }
        
        int t = 0;
        int s = 0;
        while (RP > LP)
        {
            const Coords c = Q[++LP];

            ++t;
            s = max(s, REC[c.y][c.x]);
            
            for (int i = 0; i < 4; ++i)
            {
                const Coords n = c.move(i);
                if (n.is_invalid())
                {
                    continue;
                }

                if (REC[n.y][n.x])
                {
                    continue;
                }

                REC[n.y][n.x] = REC[c.y][c.x] + 1;
                Q[++RP] = n;
            }
        }

        return t == T ? s - 1 : INF;
    }

    int ret = INF;
    for (int i = sidx; i < V; ++i)
    {
        ret = min(ret, run(i + 1, cnt + 1, (selected | (1 << i))));
    }

    return ret;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    T = N * N;
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            std::cin >> MAP[i][j];
            if (MAP[i][j] == WALL)
            {
                --T;
            }
            else if (MAP[i][j] == VIRUS)
            {
                V_LOC[V++] = { i, j };
            }
        }
    }

    int res = run(0, 0, 0);
    std::cout << (res == INF ? -1 : res);

    return 0;
}