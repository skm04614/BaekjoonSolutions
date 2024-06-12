#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[3000300];
int N;

int CNT[3030];
int D;
int K;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int c;
    std::cin >> N >> D >> K >> c;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i];
    }

    ++CNT[c];
    int max_cnt = 1;
    int cnt = 1;
    int l = 0;
    int r = 0;
    while (r < K)
    {
        if (++CNT[ARR[r++]] == 1)
        {
            ++cnt;
        }
        max_cnt = max_cnt > cnt ? max_cnt : cnt;
    }

    while (l < N)
    {
        if (--CNT[ARR[(l++ % N)]] == 0)
        {
            --cnt;
        }

        if (++CNT[ARR[(r++ % N)]] == 1)
        {
            ++cnt;
        }

        max_cnt = max_cnt > cnt ? max_cnt : cnt;
    }

    std::cout << max_cnt;

    return 0;
}