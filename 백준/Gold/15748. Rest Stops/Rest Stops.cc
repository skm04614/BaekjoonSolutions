#include <iostream>

using ull = unsigned long long;

struct Stop
{
    ull x;
    ull c;

    bool operator<=(const Stop& other) const
    {
        return c <= other.c;
    }
};

Stop STOPS[100010];

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void sort(T* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] <= arr[c])
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
            if ((c | 1) <= max_s && arr[c | 1] <= arr[c])
            {
                c |= 1;
            }

            if (arr[p] <= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

int L;
int N;
ull RF;
ull RB;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> L >> N >> RF >> RB;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> STOPS[i].x >> STOPS[i].c;
    }

    sort(STOPS, N);


    ull x = 0;
    ull res = 0;
    for (int i = 1; i <= N; ++i)
    {
        if (x >= STOPS[i].x)
        {
            continue;
        }

        res += (STOPS[i].x - x) * (RF - RB) * STOPS[i].c;
        x = STOPS[i].x;
    }
    std::cout << res;


    return 0;
}
