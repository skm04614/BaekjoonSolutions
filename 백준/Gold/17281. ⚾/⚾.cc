#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int INNINGS[51][9];
int N;

int ARR[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

int play_round(int round, int& idx)
{
    const int* inning = INNINGS[round];

    int out_cnt = 0;
    int score = 0;
    int base = 0;
    for (; ; idx = (idx + 1) % 9)
    {
        if (out_cnt == 3)
        {
            break;
        }

        if (inning[ARR[idx]] == 0)
        {
            ++out_cnt;
            continue;
        }

        base = ((base << 1) | 1) << (inning[ARR[idx]] - 1);
        int overflow = base >> 3;
        base &= 0x7;

        while (overflow)
        {
            score += overflow & 1;
            overflow >>= 1;
        }
    }

    return score;
}

int dfs(int depth, int visited)
{
    if (depth == 9)
    {
        int total_score = 0;
        int idx = 0;
        for (int n = 0; n < N; ++n)
        {
            total_score += play_round(n, idx);
        }
        return total_score;
    }

    if (depth == 3)
    {
        return dfs(depth + 1, visited);
    }

    int highest_score = 0;
    for (int n = 0; n < 9; ++n)
    {
        if (visited & (1 << n))
        {
            continue;
        }

        ARR[depth] = n;
        highest_score = max(highest_score, dfs(depth + 1, visited | (1 << n)));
    }

    return highest_score;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N;
    for (int n = 0; n < N; ++n)
    {
        for (int i = 0; i < 9; ++i)
        {
            std::cin >> INNINGS[n][i];
        }
    }

    std::cout << dfs(0, 1 << 0);

    return 0;
}
