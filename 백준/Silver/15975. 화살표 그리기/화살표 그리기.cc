#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

inline ll _abs(ll x)
{
    return x < 0 ? -x : x;
}

inline ll min(ll x, ll y)
{
    return x < y ? x : y;
}

template <typename T>
void msort(T* arr, T* tmp, int idx0, int idx1)
{
    if (idx0 == idx1)
    {
        return;
    }

    int mid = (idx0 + idx1) >> 1;
    msort(arr, tmp, idx0, mid);
    msort(arr, tmp, mid + 1, idx1);

    int left = idx0;
    int right = mid + 1;
    int idx = 0;

    for (;;)
    {
        if (left > mid || right > idx1)
        {
            break;
        }

        if (arr[left] <= arr[right])
        {
            tmp[idx++] = arr[left++];
        }
        else
        {
            tmp[idx++] = arr[right++];
        }
    }

    while (left <= mid)
    {
        tmp[idx++] = arr[left++];
    }

    while (right <= idx1)
    {
        tmp[idx++] = arr[right++];
    }

    for (int i = 0; i < idx; ++i)
    {
        arr[idx0 + i] = tmp[i];
    }
}

struct Point
{
    ll c;
    ll x;

    bool operator<=(const Point& other) const
    {
        if (c == other.c)
        {
            return x <= other.x;
        }

        return c <= other.c;
    }

    ll dist(const Point& other) const
    {
        if (c == other.c)
        {
            return _abs(x - other.x);
        }

        return 0;
    }
};

Point ARR[100100];
Point TMP[100100];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i].x >> ARR[i].c;
    }

    msort(ARR, TMP, 0, N - 1);

    ll sum = ARR[0].dist(ARR[1]) + ARR[N - 1].dist(ARR[N - 2]);
    for (int i = 1; i < N - 1; ++i)
    {
        ll tmp1 = ARR[i].dist(ARR[i - 1]);
        ll tmp2 = ARR[i].dist(ARR[i + 1]);
        if (tmp1 && tmp2)
        {
            sum += min(tmp1, tmp2);
        }
        else
        {
            sum += tmp1 + tmp2;
        }
    }
    std::cout << sum;

    return 0;
}
