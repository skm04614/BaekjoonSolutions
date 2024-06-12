#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int LEFT[51];
int L;

int RIGHT[51];
int R;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

inline int abs(int x)
{
    return x > 0 ? x : -x;
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
        while (left <= right && abs(arr[right]) >= abs(arr[pivot]))
        {
            --right;
        }

        while (left <= right && abs(arr[left]) < abs(arr[pivot]))
        {
            ++left;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            swap(pivot, right);
            break;
        }

        swap(arr[left], arr[right]);
    }

    _qsort(arr, idx0, pivot - 1);
    _qsort(arr, pivot + 1, idx1);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    std::cin >> N;

    int res = 0;
    while (N--)
    {
        int val;
        std::cin >> val;

        if (val <= 0)
        {
            LEFT[++L] = val;
        }
        else if (val == 1)
        {
            res += val;
        }
        else
        {
            RIGHT[++R] = val;
        }
    }

    _qsort(LEFT, 1, L);
    _qsort(RIGHT, 1, R);


    int l = 1;
    if (L & 1)
    {
        res += LEFT[l++];
    }

    int r = 1;
    if (R & 1)
    {
        res += RIGHT[r++];
    }

    for (int i = l; i <= L; i += 2)
    {
        res += (LEFT[i] * LEFT[i + 1]);
    }

    for (int i = r; i <= R; i += 2)
    {
        res += (RIGHT[i] * RIGHT[i + 1]);
    }

    std::cout << res;


    return 0;
}