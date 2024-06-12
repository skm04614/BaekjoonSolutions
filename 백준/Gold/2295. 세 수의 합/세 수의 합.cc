#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1010];
int N;

int S[1001000];
int M;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

inline int abs(int x)
{
    return x < 0 ? -x : x;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

bool _bsearch(const int* arr, int l, int r, int tgt)
{
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (tgt == arr[mid])
        {
            return true;
        }

        if (tgt < arr[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return false;
}

void _sort(int* arr, int size)
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

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    for (int i = 1; i <= N; ++i)
    {
        for (int j = i; j <= N; ++j)
        {
            S[++M] = ARR[i] + ARR[j];
        }
    }

    _sort(S, M);

    int res = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = i; j <= N; ++j)
        {
            int tgt = abs(ARR[i] - ARR[j]);
            if (_bsearch(S, 1, M, tgt))
            {
                res = max(res, max(ARR[i], ARR[j]));
            }
        }
    }
    std::cout << res;

    return 0;
}