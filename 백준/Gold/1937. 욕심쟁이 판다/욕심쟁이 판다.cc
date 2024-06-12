#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int MAP[501][501];
int DP[501][501];
int N;

inline int max(int n, int m)
{
    return n > m ? n : m;
}

struct Coords
{
    int y;
    int x;

    bool operator>=(const Coords & other) const
    {
        return MAP[y][x] >= MAP[other.y][other.x];
    }

    bool operator<=(const Coords& other) const
    {
        return MAP[y][x] <= MAP[other.y][other.x];
    }

    bool is_out_of_bounds() const
    {
        return y < 0 || x < 0 || y >= N || x >= N;
    }

    Coords move(int opt) const
    {
        switch (opt)
        {
        case 0:
            return { y + 1, x };
        case 1:
            return { y - 1, x };
        case 2:
            return { y, x + 1 };
        default:
            return { y, x - 1 };
        }
    }
};



inline void swap(Coords& c1, Coords& c2)
{
    Coords tmp = c1;
    c1 = c2;
    c2 = tmp;
}

struct MinHeap
{
    Coords data[250250];
    int n;

    void push(Coords c)
    {
        data[++n] = c;

        int ch = n;
        while (ch > 1)
        {
            if (data[ch] >= data[ch / 2])
            {
                break;
            }
            
            swap(data[ch], data[ch / 2]);
            ch /= 2;
        }
    }

    Coords pop(void)
    {
        Coords ret = data[1];
        swap(data[1], data[n--]);

        int p = 1;
        while (2 * p <= n)
        {
            int c1 = 2 * p;
            int c2 = c1 + 1;
            int ch = c1;

            if (c2 <= n && data[c2] <= data[c1])
            {
                ch = c2;
            }

            if (data[ch] >= data[p])
            {
                break;
            }

            swap(data[ch], data[p]);
            p = ch;
        }

        return ret;
    }

    bool empty() const
    {
        return n == 0;
    }
};

MinHeap MH;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            std::cin >> MAP[i][j];
            MH.push({ i, j });
        }
    }

    int sol = 0;
    while (!MH.empty())
    {
        const Coords current = MH.pop();
        sol = max(sol, DP[current.y][current.x] + 1);
        for (int j = 0; j < 4; j++)
        {
            const Coords next = current.move(j);
            if (next.is_out_of_bounds())
            {
                continue;
            }

            if (MAP[next.y][next.x] > MAP[current.y][current.x])
            {
                DP[next.y][next.x] = max(DP[next.y][next.x], DP[current.y][current.x] + 1);
            }
        }
    }
    std::cout << sol;

    return 0;
}