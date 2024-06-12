#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

using ull = unsigned long long;

struct BigInt
{
    static constexpr ull MOD = static_cast<ull>(1e17);

    ull data[100];
    int n;

    BigInt(ull val) : data{}, n{ }
    {
        data[0] = val % MOD;
        n = 1;

        if (val / MOD)
        {
            data[1] = val / MOD;
            n = 2;
        }
    }

    BigInt operator+(const BigInt& other) const
    {
        BigInt ret{ 0 };

        ull carry = 0;
        ret.n = n > other.n ? n : other.n;
        for (int i = 0; i < ret.n; ++i)
        {
            ret.data[i] = data[i] + other.data[i] + carry;

            carry = ret.data[i] / MOD;
            ret.data[i] %= MOD;
        }

        if (carry)
        {
            ret.data[ret.n++] = carry;
        }

        return ret;
    }

    BigInt operator+(ull val) const
    {
        return *this + BigInt{ val };
    }

    void print() const
    {
        std::cout << data[n - 1];
        for (int i = n - 2; i >= 0; --i)
        {
            std::cout << std::setfill('0') << std::setw(17) << data[i];
        }
        std::cout << '\n';
    }
};

void print_hanoi(int n, int src, int tmp, int dest)
{
    if (n == 1)
    {
        std::cout << src << ' ' << dest << '\n';
        return;
    }

    print_hanoi(n - 1, src, dest, tmp);
    std::cout << src << ' ' << dest << '\n';
    print_hanoi(n - 1, tmp, src, dest);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    std::cin >> N;

    BigInt x{ 0 };
    for (int i = 1; i <= N; ++i)
    {
        x = x + x + 1;
    }
    x.print();

    if (N <= 20)
    {
        print_hanoi(N, 1, 2, 3);
    }

    return 0;
}