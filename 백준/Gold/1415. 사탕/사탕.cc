#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int ARR[51];
int N;

int CNT[10010];
ull DP[2][500500];

bool is_prime(int v)
{
    if (v <= 1)
    {
        return false;
    }

    for (int n = 2; n * n <= v; ++n)
    {
        if (v % n == 0)
        {
            return false;
        }
    }

    return true;
}

void clear(ull* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        *(arr + i) = 0;
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
        if (ARR[i] == 0)
        {
            ++DP[0][0];
            continue;
        }

        ++CNT[ARR[i]];
    }

    ++DP[0][0];
    int sum = 0;

    int p = 0;
    int c = 1;
    for (int i = 1; i <= N; ++i)
    {
        if (CNT[ARR[i]] == 0)
        {
            continue;
        }

        for (int s = 0; s <= sum; ++s)
        {
            if (DP[p][s] == 0)
            {
                continue;
            }

            for (int ds = 0; ds <= ARR[i] * CNT[ARR[i]]; ds += ARR[i])
            {
                DP[c][s + ds] += DP[p][s];
            }
        }
        sum += ARR[i] * CNT[ARR[i]];
        CNT[ARR[i]] = 0;

        swap(p, c);
        clear(DP[c], sum + 1);
    }

    ull sol = 0;
    for (int v = 2; v <= sum; ++v)
    {
        if (!is_prime(v))
        {
            continue;
        }

        sol += DP[p][v];
    }
    std::cout << sol;

    return 0;
}
