#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
constexpr ull MOD = 1'000'000'007;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct MinHeap
{
    ull data[61];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(ull val)
    {
        data[++size] = val;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    ull pop()
    {
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1] <= data[c])
            {
                c |= 1;
            }

            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return data[size + 1];
    }
} HQ;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int T;
    std::cin >> T;
    while (T--)
    {
        HQ.size = 0;

        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i)
        {
            ull val;
            std::cin >> val;
            HQ.push(val);
        }
        
        if (n == 1)
        {
            std::cout << 1 << '\n';
            continue;
        }

        ull sol = 1;
        while (HQ.size >= 2)
        {
            ull v1 = HQ.pop();
            ull v2 = HQ.pop();
            sol = (sol * (v1 % MOD)) % MOD;
            sol = (sol * (v2 % MOD)) % MOD;
            HQ.push(v1 * v2);
        }
        std::cout << sol << '\n';
    }

    return 0;
}
