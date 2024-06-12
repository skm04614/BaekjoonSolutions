#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ll = long long;

ll ARR[5050];
int N;

inline void swap(ll& x, ll& y)
{
    ll tmp = x;
    x = y;
    y = tmp;
}

ll _abs(ll x)
{
    return x > 0 ? x : -x;
}

void sort(ll* arr, int size)
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

    sort(ARR, N);

    int idx[3] = { 1, 2, N };
    ll best = 0x7FFFFFFFFFFFFFFF;
    for (int i = 1; i <= N - 2; ++i)
    {
        int l = i + 1;
        int r = N;

        while (l < r)
        {
            const ll x = ARR[i] + ARR[l] + ARR[r];
            if (_abs(x) < _abs(best))
            {
                idx[0] = i;
                idx[1] = l;
                idx[2] = r;
                best = x;
            }

            if (x > 0)
            {
                --r;
            }
            else
            {
                ++l;
            }
        }
    }

    std::cout << ARR[idx[0]] << ' ' << ARR[idx[1]] << ' ' << ARR[idx[2]];

    return 0;
}