#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int HOR = 0;
constexpr int VER = 1;

int ORIGINAL[21];
int CURRENT[21];
int N;

void flip(int *coins, int dir, int level)
{
    if (dir == HOR)
    {
        coins[level] = ~coins[level] & ((1u << N) - 1);
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            coins[i] ^= (1u << (N - 1 - level));
        }
    }
}

int count_tails(int* coins, int dir, int level)
{
    int cnt = 0;
    if (dir == HOR)
    {
        for (int i = 0; i < N; i++)
        {
            cnt += (coins[level] & (1u << i)) > 0;
        }
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            cnt += (coins[i] & (1u << (N - 1 - level))) > 0;
        }
    }
    return cnt;
}

void init(int v)
{
    for (int lv = 0; lv < N; lv++)
    {
        CURRENT[lv] = ORIGINAL[lv];

        if (v & (1u << lv))
        {
            flip(CURRENT, HOR, lv);
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        ORIGINAL[i] = 0;
        for (int j = 0; j < N; j++)
        {
            char c;
            std::cin >> c;
            ORIGINAL[i] = (ORIGINAL[i] << 1) | (c == 'T');
        }
    }

    int sol = 0x7FFFFFFF;
    for (int v = 0; v < (1u << N); v++)
    {
        init(v);

        int cnt = 0;
        for (int i = 0; i < N; i++)
        {
            int tail_cnt = count_tails(CURRENT, VER, i);
            if (2 * tail_cnt > N)
            {
                flip(CURRENT, VER, i);
                cnt += (N - tail_cnt);
            }
            else
            {
                cnt += tail_cnt;
            }
        }
        sol = sol < cnt ? sol : cnt;
    }
    std::cout << sol;


    return 0;
}