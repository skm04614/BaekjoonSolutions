#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void _qsort(T* arr, int idx0, int idx1)
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
        while (left <= right && arr[pivot] <= arr[right])
        {
            --right;
        }

        while (left <= right && arr[pivot] >= arr[left])
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

struct Parcel
{
    int s;
    int e;
    int v;

    bool operator>=(const Parcel& other) const
    {
        if (s == other.s)
        {
            return e >= other.e;
        }

        return s < other.s;
    }

    bool operator<=(const Parcel& other) const
    {
        if (s == other.s)
        {
            return e <= other.e;
        }

        return s > other.s;
    }
};

int REC[2020];
int N, K;

Parcel PARCELS[10100];
int P;

int query_max(int idx0, int idx1)
{
    ++idx0;

    int res = 0;
    for (int i = idx0; i <= idx1; ++i)
    {
        res = max(res, REC[i]);
    }

    return res;
}

void add(int idx0, int idx1, int k)
{
    ++idx0;

    for (int i = idx0; i <= idx1; ++i)
    {
        REC[i] += k;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K >> P;
    for (int i = 1; i <= P; ++i)
    {
        std::cin >> PARCELS[i].s >> PARCELS[i].e >> PARCELS[i].v;
    }

    _qsort(PARCELS, 1, P);

    int res = 0;
    for (int i = 1; i <= P; ++i)
    {
        const Parcel& p = PARCELS[i];
        int k = min(p.v, K - query_max(p.s, p.e));
        res += k;
        add(p.s, p.e, k);
    }
    std::cout << res;

    return 0;
}
