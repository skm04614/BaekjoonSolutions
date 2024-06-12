#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[41];
int N;
int K;

int SUM_1[1 << 21];
int M1;
int SUM_2[1 << 21];
int M2;

int dfs(const int* arr, int* rec, int idx, int sum, int depth, int D)
{
    if (depth == D)
    {
        rec[++idx] = sum;
        return idx;
    }

    idx = dfs(arr, rec, idx, sum, depth + 1, D);
    idx = dfs(arr, rec, idx, sum + arr[depth], depth + 1, D);

    return idx;
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

            int p = c >> 1;
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

int count(int* arr, int left, int right, int tgt)
{
    int l1 = left;
    int r1 = right;
    for (;;)
    {
        if (l1 > r1)
        {
            break;
        }

        int mid = (l1 + r1) >> 1;
        if (tgt <= arr[mid])
        {
            r1 = mid - 1;
        }
        else
        {
            l1 = mid + 1;
        }
    }

    int l2 = left;
    int r2 = right;
    for (;;)
    {
        if (l2 > r2)
        {
            break;
        }

        int mid = (l2 + r2) >> 1;
        if (tgt < arr[mid])
        {
            r2 = mid - 1;
        }
        else
        {
            l2 = mid + 1;
        }
    }

    return r2 - l1 + 1;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i];
    }

    int mid = (N + 1) / 2;
    M1 = dfs(ARR, SUM_1, 0, 0, 0, mid);
    M2 = dfs(ARR + mid, SUM_2, 0, 0, 0, N - mid);

    sort(SUM_1, M1);
    sort(SUM_2, M2);

    unsigned long long sol = 0llu;
    for (int i = 1; i <= M2; ++i)
    {
        int tgt = K - SUM_2[i];
        sol += count(SUM_1, 1, M1, tgt);
    }

    if (K == 0)
    {
        --sol;
    }
    std::cout << sol;

    return 0;
}