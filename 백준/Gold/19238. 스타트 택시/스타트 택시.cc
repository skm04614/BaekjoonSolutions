#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int MAP[21][21];
int COST[21][21];
int N;

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
            return { y - 1, x };
        }
        else if (opt == 2)
        {
            return { y, x + 1 };
        }
        else
        {
            return { y, x - 1 };
        }
    }

    bool is_invalid() const
    {
        return y < 1 || y > N || x < 1 || x > N || MAP[y][x];
    }
};

struct Passenger
{
    Coords start;
    Coords end;
    bool done;

    bool operator>=(const Passenger& other) const
    {
        if (start.y == other.start.y)
        {
            return start.x >= other.start.x;
        }

        return start.y > other.start.y;
    }
};

inline void swap(Passenger& x, Passenger& y)
{
    Passenger tmp = x;
    x = y;
    y = tmp;
}

void sort(Passenger* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);

        const int max_s = s - 1;
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
            {
                c |= 1;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

Coords TAXI;

Passenger PASSENGERS[410];
int M;

int F;

Coords Q[410];
int LP;
int RP;

void bfs()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            COST[i][j] = 0;
        }
    }

    LP = RP = -1;
    Q[++RP] = TAXI;
    COST[TAXI.y][TAXI.x] = 1;

    while (RP > LP)
    {
        const Coords c = Q[++LP];

        for (int i = 0; i < 4; ++i)
        {
            const Coords n = c.move(i);

            if (n.is_invalid() || COST[n.y][n.x])
            {
                continue;
            }

            Q[++RP] = n;
            COST[n.y][n.x] = COST[c.y][c.x] + 1;
        }
    }
}

int sol()
{
    int p_cnt = M;
    while (p_cnt)
    {
        bfs();

        int cost = INF;
        int idx = 0;
        for (int m = 1; m <= M; ++m)
        {
            Passenger& p = PASSENGERS[m];

            if (p.done || COST[p.start.y][p.start.x] == 0)
            {
                continue;
            }

            if (COST[p.start.y][p.start.x] < cost)
            {
                cost = COST[p.start.y][p.start.x];
                idx = m;
            }
        }

        if (idx == 0)
        {
            return -1;
        }

        F -= (cost - 1);

        Passenger& p = PASSENGERS[idx];
        TAXI = p.start;

        bfs();

        if (COST[p.end.y][p.end.x] == 0)
        {
            return -1;
        }

        cost = COST[p.end.y][p.end.x] - 1;
        F -= cost;
        if (F < 0)
        {
            return -1;
        }

        TAXI = p.end;
        F += 2 * cost;

        p.done = true;
        --p_cnt;
    }

    return F;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M >> F;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            std::cin >> MAP[i][j];
        }
    }

    std::cin >> TAXI.y >> TAXI.x;
    for (int i = 1; i <= M; ++i)
    {
        Passenger& p = PASSENGERS[i];
        p.done = false;
        std::cin >> p.start.y >> p.start.x >> p.end.y >> p.end.x;
    }

    sort(PASSENGERS, M);

    std::cout << sol();

    return 0;
}