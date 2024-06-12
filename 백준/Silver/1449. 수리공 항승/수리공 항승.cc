#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1010];
int N;
int L;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void sort(int* arr, int size)
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

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> L;
    --L;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    sort(ARR, N);

    int res = 0;
    int i = 1;
    while (i <= N)
    {
        int j = i + 1;
        for (; j <= N && ARR[j] - ARR[i] <= L; ++j);
        i = j;
        ++res;
    }
    std::cout << res;

    return 0;
}