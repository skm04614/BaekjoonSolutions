#include <iostream>

int LEFT[51];
int L;

int RIGHT[51];
int R;

int TMP[51];
int T;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

inline int _min(int x, int y)
{
    return x < y ? x : y;
}

inline int _abs(int x)
{
    return x < 0 ? -x : x;
}

void _msort(int* arr, int* tmp, int left, int right)
{
    if (left == right)
    {
        return;
    }

    int mid = (left + right) >> 1;
    _msort(arr, tmp, left, mid);
    _msort(arr, tmp, mid + 1, right);

    int l = left;
    int r = mid + 1;
    int idx = 0;
    for (;;)
    {
        if (l > mid || r > right)
        {
            break;
        }

        if (abs(arr[l]) < abs(arr[r]))
        {
            tmp[idx++] = arr[l++];
        }
        else
        {
            tmp[idx++] = arr[r++];
        }
    }

    while (l <= mid)
    {
        tmp[idx++] = arr[l++];
    }

    while (r <= right)
    {
        tmp[idx++] = arr[r++];
    }

    for (int i = 0; i < idx; ++i)
    {
        arr[left + i] = tmp[i];
    }
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
        while (left <= right && arr[right] >= arr[pivot])
        {
            --right;
        }

        while (left <= right && arr[left] <= arr[pivot])
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

    int N, M;
    std::cin >> N >> M;
    for (int i = 0; i < N; ++i)
    {
        int val;
        std::cin >> val;
        if (val < 0)
        {
            LEFT[L++] = val;
        }
        else
        {
            RIGHT[R++] = val;
        }
    }

    if (L)
    {
        _msort(LEFT, TMP, 0, L - 1);
    }
    if (R)
    {
        _msort(RIGHT, TMP, 0, R - 1);
    }

    while (L > 0)
    {
        TMP[T++] = _abs(LEFT[L - 1]);

        L -= M;
    }

    while (R > 0)
    {
        TMP[T++] = _abs(RIGHT[R - 1]);

        R -= M;
    }

    _qsort(TMP, 0, T - 1);

    int res = 0;
    for (int i = 0; i < T - 1; ++i)
    {
        res += (TMP[i] << 1);
    }
    std::cout << (res + TMP[T - 1]);


    return 0;
}
