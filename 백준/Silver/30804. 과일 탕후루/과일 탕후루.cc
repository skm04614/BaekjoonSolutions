#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[200100];
int CNT[10];
int N;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int count_nonzero_cnt()
{
    int res = 0;
    for (int i = 0; i < 10; ++i)
    {
        if (CNT[i])
        {
            ++res;
        }
    }

    return res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N;

    int res = 0;
    int left = 1;
    for (int right = 1; right <= N; ++right)
    {
        std::cin >> ARR[right];
        ++CNT[ARR[right]];

        while (count_nonzero_cnt() > 2)
        {
            --CNT[ARR[left++]];
        }

        res = max(res, right - left + 1);
    }

    std::cout << res;

    return 0;
}
