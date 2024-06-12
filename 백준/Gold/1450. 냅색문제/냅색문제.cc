#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[31];
int N;
int C;

ull S1[1 << 16];
int M1;
ull S2[1 << 16];
int M2;

inline void swap(ull& x, ull& y)
{
    ull tmp = x;
    x = y;
    y = tmp;
}

int dfs(const ull* arr, ull* dest, int idx, int depth, ull sum, int D)
{
    if (depth == D)
    {
        dest[++idx] = sum;
        return idx;
    }

    idx = dfs(arr, dest, idx, depth + 1, sum, D);
    idx = dfs(arr, dest, idx, depth + 1, sum + arr[depth], D);

    return idx;
}

void sort(ull* arr, int size)
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

int ubound(const ull* arr, int l, int r, ull tgt)
{
    for (;;)
    {
        if (l > r)
        {
            break;
        }

        int mid = (l + r) >> 1;
        if (tgt < arr[mid])
        {
            r = mid - 1;
        }
        else
        {
            l = mid + 1;
        }
    }

    return r;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> C;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i];
    }

    int mid = (N + 1) >> 1;
    M1 = dfs(ARR, S1, 0, 0, 0, mid);
    M2 = dfs(ARR + mid, S2, 0, 0, 0, N - mid);

    sort(S1, M1);
    sort(S2, M2);

    ull res = 0;
    for (int i = 1; i <= M1; ++i)
    {
        if (S1[i] > C)
        {
            break;
        }

        res += ubound(S2, 1, M2, C - S1[i]);
    }
    std::cout << res;


    return 0;
}