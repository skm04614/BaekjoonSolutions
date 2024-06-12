#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

char BUF[1'000'100];
int PM[1'000'100];
int L;

int PM2[1'000'100];
int L2;

int CNT[1'000'100];

void fill_pmatch(const char* s, int size, int* pmatch)
{
    pmatch[0] = 0;
    int len = 0;
    
    for (int i = 1; i < size; ++i)
    {
        while (len && s[i] != s[len])
        {
            len = pmatch[len - 1];
        }

        if (s[i] == s[len])
        {
            ++len;
        }

        pmatch[i] = len;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;
    L = _slen(BUF);

    fill_pmatch(BUF, L, PM);

    L2 = PM[L - 1];
    fill_pmatch(BUF + L - PM[L - 1], L2, PM2);

    int res = PM2[L2 - 1];
    for (int i = 0; i < L; ++i)
    {
        ++CNT[PM[i]];
    }
    
    if (CNT[PM[L - 1]] >= 2)
    {
        res = max(res, PM[L - 1]);
    }

    if (res == 0)
    {
        std::cout << -1;
    }
    else
    {
        BUF[res] = 0;

        std::cout << BUF;
    }

    return 0;
}