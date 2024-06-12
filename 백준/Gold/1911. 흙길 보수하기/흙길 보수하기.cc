#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

template <typename T>
void sort(T* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = pivot + 1;
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

    sort(arr, idx0, right - 1);
    sort(arr, right + 1, idx1);
}

struct Element
{
    int l;
    int r;

    bool operator>=(const Element& other) const
    {
        return l >= other.l;
    }

    bool operator<=(const Element& other) const
    {
        return l <= other.l;
    }
};

Element ARR[10010];
int N;
int L;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> L;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i].l >> ARR[i].r;
    }

    sort(ARR, 0, N - 1);

    int cnt = 0;
    int r = 0;
    for (int i = 0; i < N; ++i)
    {
        if (ARR[i].r <= r)
        {
            continue;
        }

        r = max(r, ARR[i].l);
        for (; r < ARR[i].r; r += L, ++cnt);
    }
    std::cout << cnt;

    return 0;
}
