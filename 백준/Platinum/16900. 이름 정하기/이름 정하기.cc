#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char KEY[500500];
int PMATCH[500500];
int K;

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

unsigned long long sol(unsigned long long x)
{
    K = _slen(KEY);

    PMATCH[0] = 0;
    int len = 0;
    for (int i = 1; i < K; i++)
    {
        while (len && KEY[i] != KEY[len])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[i] == KEY[len])
        {
            ++len;
        }

        PMATCH[i] = len;
    }

    return x * (K - PMATCH[K - 1]) + PMATCH[K - 1];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    unsigned long long X;
    std::cin >> KEY >> X;

    std::cout << sol(X);

    return 0;
}