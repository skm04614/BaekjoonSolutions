#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

inline ll max(ll x, ll y)
{
    return x > y ? x : y;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void q_sort(T* arr, int idx0, int idx1)
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
        while (left <= right && arr[right] < arr[pivot])
        {
            --right;
        }

        while (left <= right && arr[left] >= arr[pivot])
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

    q_sort(arr, idx0, right - 1);
    q_sort(arr, right + 1, idx1);
}

struct Coords
{
    ll y;
    ll x;
    ll c;

    bool operator>=(const Coords& other) const
    {
        return c >= other.c;
    }

    bool operator<(const Coords& other) const
    {
        return c < other.c;
    }

    bool is_reachable(const Coords& other) const
    {
        return y >= other.y && x >= other.x;
    }
};

Coords ARR[310];
int N;

ll DP[310];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    int M;
    std::cin >> n >> M;
    for (int i = 1; i <= n; ++i)
    {
        ll x, y;
        std::cin >> x >> y;
        ll c = M - (y + x);
        if (c <= 0)
        {
            continue;
        }

        ARR[++N] = { y, x, c };
    }
    ARR[0] = { 0, 0, 0 };

    q_sort(ARR, 1, N);

    ll res = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 0; j <= i - 1; ++j)
        {
            if (ARR[i].is_reachable(ARR[j]))
            {
                DP[i] = max(DP[i], DP[j] + ARR[i].c);
                res = max(res, DP[i]);
            }
        }
    }
    std::cout << res;

    return 0;
}
