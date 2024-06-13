#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

const char MOVE[5] = "LURD";

char MAP[11][11];
int Y, X;

struct Coords
{
    int y;
    int x;

    void move(int opt)
    {
        if (opt == 0)
        {
            --x;
            return;
        }

        if (opt == 1)
        {
            --y;
            return;
        }

        if (opt == 2)
        {
            ++x;
            return;
        }

        ++y;
    }

    void move_rvsd(int opt)
    {
        move((opt + 2) % 4);
    }

    bool is_exit() const
    {
        return MAP[y][x] == 'O';
    }

    bool is_invalid() const
    {
        return MAP[y][x] == '#';
    }

    bool operator==(const Coords& other) const
    {
        return y == other.y && x == other.x;
    }
};

struct CoordsPair
{
    Coords blue;
    Coords red;

    CoordsPair move(int opt) const
    {
        Coords new_blue = blue;
        Coords new_red = red;

        for (;;)
        {
            new_blue.move(opt);
            if (new_blue.is_exit())
            {
                break;
            }

            if (new_blue == new_red || new_blue.is_invalid())
            {
                new_blue.move_rvsd(opt);
                break;
            }
        }

        for (;;)
        {
            new_red.move(opt);
            if (new_red.is_exit())
            {
                break;
            }

            if (new_red == new_blue || new_red.is_invalid())
            {
                new_red.move_rvsd(opt);
                break;
            }
        }

        if (!new_blue.is_exit())
        {
            for (;;)
            {
                new_blue.move(opt);
                if (new_blue.is_exit())
                {
                    break;
                }

                if (new_blue == new_red || new_blue.is_invalid())
                {
                    new_blue.move_rvsd(opt);
                    break;
                }
            }
        }

        return { new_blue, new_red };
    }

    bool is_fail() const
    {
        return blue.is_exit();
    }

    bool is_success() const
    {
        return red.is_exit();
    }

    int hash() const
    {
        return blue.y * 1000 + red.y * 100 + blue.x * 10 + red.x;
    }
};

Coords BLUE;
Coords RED;

void record(char* dest, const char* src, char last_move)
{
    while (*dest = *src)
    {
        ++src;
        ++dest;
    }
    *dest++ = last_move;
    *dest = 0;
}

char RECORD[10100][11];
int VISITED[10100];
CoordsPair Q[10100];
int LP, RP;


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
            std::cin >> MAP[y][x];

            if (MAP[y][x] == 'B')
            {
                BLUE = { y, x };
                MAP[y][x] = '.';
            }
            else if (MAP[y][x] == 'R')
            {
                RED = { y, x };
                MAP[y][x] = '.';
            }
        }
    }

    int sol = -1;
    int sol_hash = -1;

    CoordsPair init = { BLUE, RED };
    Q[++RP] = init;
    VISITED[init.hash()] = 1;
    while (RP > LP)
    {
        const CoordsPair& c = Q[++LP];
        if (VISITED[c.hash()] > 10)
        {
            break;
        }

        for (int i = 0; i < 4; ++i)
        {
            const CoordsPair n = c.move(i);
            if (n.is_fail())
            {
                continue;
            }

            if (VISITED[n.hash()])
            {
                continue;
            }

            record(RECORD[n.hash()], RECORD[c.hash()], MOVE[i]);
            if (n.is_success())
            {
                sol = VISITED[c.hash()];
                
                sol_hash = n.hash();
                RP = LP;
                break;
            }

            VISITED[n.hash()] = 1 + VISITED[c.hash()];
            Q[++RP] = n;
        }
    }

    std::cout << sol << '\n';
    if (sol != -1)
    {
        std::cout << RECORD[sol_hash];
    }

    return 0;
}
