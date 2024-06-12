#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Array
{
    int data[330][330];
    int Y;
    int X;

    int encoded_data[165][1320];
    int level_size[165];
    int sidx[165];
    int max_level;

    void init(int Y, int X, int (*arr)[330])
    {
        this->Y = Y;
        this->X = X;
        for (int i = 1; i <= Y; ++i)
        {
            for (int j = 1; j <= X; ++j)
            {
                data[i][j] = arr[i][j];
            }
        }
    }

    void encode()
    {
        for (int i = 0; i < sizeof(level_size) / sizeof(level_size[0]); ++i)
        {
            level_size[i] = 0;
        }

        max_level = min(Y, X) / 2;

        for (int lv = 0; lv < max_level; ++lv)
        {
            int& lv_sz = level_size[lv];

            for (int x = 1 + lv; x <= X - 1 - lv; ++x)
            {
                encoded_data[lv][lv_sz++] = data[1 + lv][x];
            }

            for (int y = 1 + lv; y <= Y - 1 - lv; ++y)
            {
                encoded_data[lv][lv_sz++] = data[y][X - lv];
            }

            for (int x = X - lv; x >= 2 + lv; --x)
            {
                encoded_data[lv][lv_sz++] = data[Y - lv][x];
            }

            for (int y = Y - lv; y >= 2 + lv; --y)
            {
                encoded_data[lv][lv_sz++] = data[y][1 + lv];
            }
        }
    }

    void decode()
    {
        for (int lv = 0; lv < max_level; ++lv)
        {
            int idx = sidx[lv];

            for (int x = 1 + lv; x <= X - 1 - lv; ++x)
            {
                data[1 + lv][x] = encoded_data[lv][idx];
                idx = (idx + 1) % level_size[lv];
            }

            for (int y = 1 + lv; y <= Y - 1 - lv; ++y)
            {
                data[y][X - lv] = encoded_data[lv][idx];
                idx = (idx + 1) % level_size[lv];
            }

            for (int x = X - lv; x >= 2 + lv; --x)
            {
                data[Y - lv][x] = encoded_data[lv][idx];
                idx = (idx + 1) % level_size[lv];
            }

            for (int y = Y - lv; y >= 2 + lv; --y)
            {
                data[y][1 + lv] = encoded_data[lv][idx];
                idx = (idx + 1) % level_size[lv];
            }
        }
    }

    void rotate(int r)
    {
        encode();

        for (int lv = 0; lv < max_level; ++lv)
        {
            sidx[lv] = r % level_size[lv];
        }

        decode();
    }

    void print() const
    {
        for (int y = 1; y <= Y; ++y)
        {
            for (int x = 1; x <= X; ++x)
            {
                std::cout << data[y][x] << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }
};

// a b c d e f

Array ARR;
int DATA[330][330];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int Y, X, R;
    std::cin >> Y >> X >> R;
    for (int i = 1; i <= Y; ++i)
    {
        for (int j = 1; j <= X; ++j)
        {
            std::cin >> DATA[i][j];
        }
    }
    ARR.init(Y, X, DATA);
    ARR.rotate(R);
    ARR.print();

    return 0;
}
