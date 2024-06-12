#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

int PRIMES[300000];
int P;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int p = 2; p <= 4000000; p++)
    {
        bool is_prime = true;
        auto max = sqrt(p) + 1;
        for (int i = 0; i < P; i++)
        {
            if (PRIMES[i] >= max)
            {
                break;
            }

            if (p % PRIMES[i] == 0)
            {
                is_prime = false;
                break;
            }
        }

        if (is_prime)
        {
            PRIMES[P++] = p;
        }
    }
    
    int N;
    std::cin >> N;

    int cnt = 0;
    int left = 0;
    int right = 0;
    int sum = PRIMES[0];
    while (left <= P && right <= P)
    {
        if (sum == N)
        {
            cnt++;
            sum -= PRIMES[left++];
        }
        else if (sum < N)
        {
            sum += PRIMES[++right];
        }
        else
        {
            sum -= PRIMES[left++];
        }
    }
    std::cout << cnt;



    return 0;
}