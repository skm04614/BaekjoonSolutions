#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void sort(T* arr, int size)
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

struct Test
{
    int d;
    int v;

    bool operator>=(const Test& other) const
    {
        return d >= other.d;
    }
};

Test TESTS[12];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    N = 11;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> TESTS[i].d >> TESTS[i].v;
    }

    sort(TESTS, N);

    int res = 0;
    int acc = 0;
    for (int i = 1; i <= N; ++i)
    {
        acc += TESTS[i].d;
        res += acc + 20 * TESTS[i].v;
    }
    std::cout << res;

    return 0;
}