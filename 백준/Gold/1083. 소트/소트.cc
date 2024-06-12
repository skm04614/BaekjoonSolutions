#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[51];
int N;
int M;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i];
    }

    std::cin >> M;
    for (int i = 0; i < N; ++i)
    {
        int max = ARR[i];
        int idx = i;
        for (int j = i + 1; j < N && (j - i) <= M; ++j)
        {
            if (ARR[j] > max)
            {
                max = ARR[j];
                idx = j;
            }
        }

        if (idx == i)
        {
            continue;
        }

        while (M && idx > i)
        {
            swap(ARR[idx], ARR[idx - 1]);
            --idx;
            --M;
        }

        if (M == 0)
        {
            break;
        }
    }

    for (int i = 0; i < N; ++i)
    {
        std::cout << ARR[i] << ' ';
    }

    return 0;
}
