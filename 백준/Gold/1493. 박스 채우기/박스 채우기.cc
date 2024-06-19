#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
inline void order_descending(T& x, T& y, T& z)
{
    if (x < y)
    {
        swap(x, y);
    }

    if (x < z)
    {
        swap(x, z);
    }

    if (y < z)
    {
        swap(y, z);
    }
}

ull TARGET[21];
ull POOL[21];

void init(ull a, ull b, ull c)
{
    order_descending(a, b, c);

    if (c == 0)
    {
        return;
    }

    int exponent = 0;
    for (exponent = 0; (1llu << (exponent + 1)) <= c; ++exponent);

    const ull x = (1llu << exponent);
    const ull na = a / x;
    const ull nb = b / x;
    const ull nc = 1;

    TARGET[exponent] += na * nb * nc;

    init(a - (na * x), b, c);
    init(na * x, b - (nb * x), c);
    init(na * x, nb * x, c - (nc * x));
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int a, b, c;
    std::cin >> a >> b >> c;
    init(a, b, c);

    int n;
    std::cin >> n;
    while (n--)
    {
        int exponent;
        std::cin >> exponent;
        std::cin >> POOL[exponent];
    }

    ull res = 0;
    bool success = true;
    for (int exp = 20; exp >= 0; --exp)
    {
        ull target_volume = (1llu << (3 * exp)) * TARGET[exp];
        for (int i = exp; i >= 0; --i)
        {
            ull max_volume = (1llu << (3 * i)) * POOL[i];
            if (target_volume > max_volume)
            {
                target_volume -= max_volume;
                res += POOL[i];
                POOL[i] = 0;
            }
            else
            {
                ull cnt = target_volume >> (3 * i);
                res += cnt;
                POOL[i] -= cnt;
                target_volume = 0;
                break;
            }
        }

        if (target_volume)
        {
            success = false;
            break;
        }
    }

    if (success)
    {
        std::cout << res;
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}
