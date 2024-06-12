#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INVALID = -1;
constexpr int WARP = -2;
constexpr int INF = 0x7FFFFFFF;

int MAP[33][33];
int W;
int H;

struct Edge
{
    int v0;
    int v1;
    int w;
    Edge* next;

    Edge(int v0, int v1, int w, Edge* next) : v0{ v0 }, v1{ v1 }, w{ w }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Edge* E;
int COST[930];
int N;

struct Coords
{
    int y;
    int x;

    int hash() const
    {
        return y * W + x;
    }

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

    bool is_invalid() const
    {
        return MAP[y][x] == INVALID || y < 0 || x < 0 || y >= H || x >= W;
    }

    bool is_warp() const
    {
        return MAP[y][x] == WARP;
    }

    bool is_destination() const
    {
        return y == H - 1 && x == W - 1;
    }
};

void init()
{
    delete E;
    E = nullptr;

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
        {
            MAP[i][j] = 0;
        }
    }

    COST[0] = 0;
    for (int i = 1; i < N; ++i)
    {
        COST[i] = INF;
    }
}

void fill_edges()
{
    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            const Coords curr = { y, x };
            const int v0 = curr.hash();

            if (curr.is_warp() || curr.is_destination() || curr.is_invalid())
            {
                continue;
            }

            for (int i = 0; i < 4; ++i)
            {
                const Coords next = curr.move(i);
                const int v1 = next.hash();

                if (next.is_invalid())
                {
                    continue;
                }

                E = new Edge{ v0, v1, 1, E };
            }
        }
    }
}

bool bf_cycle()
{
    bool changed = false;
    for (const Edge* e = E; e; e = e->next)
    {
        if (COST[e->v0] == INF)
        {
            continue;
        }

        if (COST[e->v1] > COST[e->v0] + e->w)
        {
            COST[e->v1] = COST[e->v0] + e->w;
            changed = true;
        }
    }
    
    return changed;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (;;)
    {
        std::cin >> W >> H;
        N = W * H;
        if (W == 0 && H == 0)
        {
            break;
        }

        init();

        int X;
        std::cin >> X;
        while (X--)
        {
            int x, y;
            std::cin >> x >> y;
            MAP[y][x] = INVALID;
        }

        int Y;
        std::cin >> Y;
        for (int k = 1; k <= Y; ++k)
        {
            Coords c0, c1;
            int w;
            std::cin >> c0.x >> c0.y >> c1.x >> c1.y >> w;
            MAP[c0.y][c0.x] = WARP;

            E = new Edge{ c0.hash(), c1.hash(), w, E };
        }

        fill_edges();

        for (int i = 0; i < N - 1; ++i)
        {
            bf_cycle();
        }

        if (bf_cycle())
        {
            std::cout << "Never";
        }
        else if (COST[N - 1] == INF)
        {
            std::cout << "Impossible";
        }
        else
        {
            std::cout << COST[N - 1];
        }
        std::cout << '\n';

        delete E;
        E = nullptr;
    }

    return 0;
}