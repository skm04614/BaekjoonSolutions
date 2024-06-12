#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[200200];
char KEY[100100];
int PMATCH[100100];
int K;

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { len++; };
    return len;
}

void init_pmatch()
{
    PMATCH[0] = 0;
    int len = 0;
    for (int i = 1; i < K; i++)
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

int sol()
{
    int res = 0;

    init_pmatch();

    int j = 0;
    for (int i = 0; i < 2 * K - 1; i++)
    {
        if (j && KEY[j] != BUF[i])
        {
            j = PMATCH[j - 1];
        }

        if (KEY[j] == BUF[i])
        {
            ++j;
        }

        if (j == K)
        {
            ++res;

            j = PMATCH[K - 1];
        }
    }

    return res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF >> KEY;
    K = _slen(KEY);
    for (int i = K; i < 2 * K - 1; i++)
    {
        BUF[i] = BUF[i - K];
    }
    BUF[2 * K - 1] = 0;

    std::cout << sol();

    return 0;
}