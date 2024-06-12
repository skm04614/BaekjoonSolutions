#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int LIMIT[51];
int CNT[51];
int N;

int BOX[10010];
int M;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void _qsort(int* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = idx0 + 1;
    int right = idx1;
    for (;;)
    {
        while (left <= right && arr[right] <= arr[pivot])
        {
            --right;
        }

        while (left <= right && arr[left] > arr[pivot])
        {
            ++left;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            break;
        }

        swap(arr[left], arr[right]);
    }

    _qsort(arr, idx0, right - 1);
    _qsort(arr, right + 1, idx1);
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> LIMIT[i];
    }

    std::cin >> M;
    for (int i = 1; i <= M; ++i)
    {
        std::cin >> BOX[i];
    }

    _qsort(LIMIT, 1, N);
    _qsort(BOX, 1, M);

    if (BOX[1] > LIMIT[1])
    {
        std::cout << -1;
        return 0;
    }

    int res = 0;
    for (int i = 1; i <= M; ++i)
    {
        int j = 1;
        int min_cnt = 0x7FFFFFFF;
        for (int k = 1; k <= N; ++k)
        {
            if (BOX[i] > LIMIT[k])
            {
                break;
            }

            if (CNT[k] < min_cnt)
            {
                j = k;
                min_cnt = CNT[k];
            }
        }

        res = max(res, ++CNT[j]);
    }
    std::cout << res;

    return 0;
}