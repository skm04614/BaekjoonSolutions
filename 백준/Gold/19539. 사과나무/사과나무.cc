#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline void swap(int& x, int& y)
{
    int tmp = x;
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


int ARR[100100];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    sort(ARR, N);

    int cnt_1 = 0;
    int cnt_2 = 0;
    for (int i = 1; i <= N; ++i)
    {
        int val = ARR[i];

        int x = min(cnt_1, val / 2);
        cnt_1 -= x;
        val -= 2 * x;

        int y = min(cnt_2, val);
        cnt_2 -= y;
        val -= y;

        val %= 3;
        if (val == 0)
        {
            continue;
        }

        ++(val == 1 ? cnt_1 : cnt_2);
    }
    std::cout << (cnt_1 + cnt_2 == 0 ? "YES" : "NO");

    return 0;
}
