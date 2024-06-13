#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[22];
int N;
bool OCCURRED[2002000];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> ARR[i];
    }

    for (int n = 0; n < (1 << N); ++n)
    {
        int val = 0;
        for (int i = 0; i < N; ++i)
        {
            if (n & (1 << i))
            {
                val += ARR[i];
            }
        }
        OCCURRED[val] = true;
    }

    for (int n = 0; n <= 2000000; ++n)
    {
        if (OCCURRED[n] == false)
        {
            std::cout << n;
            break;
        }
    }



    return 0;
}
