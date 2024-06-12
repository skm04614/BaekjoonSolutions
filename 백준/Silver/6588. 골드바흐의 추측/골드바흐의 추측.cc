#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

bool is_prime(int n)
{
    if (n <= 1)
    {
        return false;
    }

    for (int i = 2; i * i <= n; ++i)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

int PRIME_NUMS[1000100];
int P;
bool PRIME[1000100];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int n = 0; n <= 1000000; ++n)
    {
        if (is_prime(n))
        {
            PRIME[n] = true;
            PRIME_NUMS[++P] = n;
        }
    }

    int val;
    for (;;)
    {
        std::cin >> val;
        if (val == 0)
        {
            break;
        }

        for (int p = 1; p <= P; ++p)
        {
            if (PRIME_NUMS[p] > val / 2)
            {
                std::cout << "Goldbach's conjecture is wrong.\n";
                break;
            }

            if (PRIME[val - PRIME_NUMS[p]])
            {
                std::cout << val << " = " << PRIME_NUMS[p] << " + " << val - PRIME_NUMS[p] << '\n';
                break;
            }
        }
    }

    return 0;
}
