#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int N;

unsigned long long sol(unsigned long long target)
{
    unsigned long long left = 0;
    unsigned long long right = static_cast<unsigned long long>(1e19);
    while (left <= right)
    {
        unsigned long long mid = (left + right) >> 1;

        unsigned long long cnt = 0;
        for (int i = 1; i <= N; ++i)
        {
            cnt += mid / ARR[i];
        }

        if (cnt >= target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
    unsigned long long T;
    std::cin >> N >> T;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    std::cout << sol(T);

    return 0;
}
