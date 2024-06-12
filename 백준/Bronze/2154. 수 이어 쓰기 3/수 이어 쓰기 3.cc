#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[600600];
int B;

inline void swap(char& x, char& y)
{
    char tmp = x;
    x = y;
    y = tmp;
}

void srev(char* s, int len)
{
    int i_max = len / 2;
    for (int i = 0; i < i_max; ++i)
    {
        swap(*(s + i), *(s + len - 1 - i));
    }
}

char KEY[10];
int PMATCH[10];
int K;

void fill_pmatch()
{
    PMATCH[0] = 0;
    int len = 0;

    for (int i = 1; i < K; ++i)
    {
        while (len && KEY[len] != KEY[i])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[len] == KEY[i])
        {
            ++len;
        }

        PMATCH[i] = len;
    }
}

void sol()
{
    int len = 0;
    for (int i = 0; i < B; ++i)
    {
        while (len && KEY[len] != BUF[i])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[len] == BUF[i])
        {
            ++len;
        }

        if (len == K)
        {
            std::cout << (i - K + 2);
            return;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char* ptr = BUF;
    for (int n = 100000; n >= 1; --n)
    {
        int val = n;
        while (val)
        {
            *ptr++ = '0' + val % 10;
            val /= 10;
        }
    }
    B = ptr - BUF;
    srev(BUF, B);

    char* p = KEY;
    int N;
    std::cin >> N;
    while (N)
    {
        *p++ = '0' + N % 10;
        N /= 10;
    }
    K = p - KEY;
    srev(KEY, K);

    fill_pmatch();

    sol();

    return 0;
}