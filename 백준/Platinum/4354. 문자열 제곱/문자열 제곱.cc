#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char KEY[1001000];
int PMATCH[1001000];
int K;

int _slen(const char* s)
{
    int len = 0;
    while (*s++)
    {
        ++len;
    }
    return len;
}

void sol(void)
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

    if (K % (K - PMATCH[K - 1]))
    {
        std::cout << 1 << '\n';
    }
    else
    {
        std::cout << K / (K - PMATCH[K - 1]) << '\n';
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (;;)
    {
        std::cin.getline(KEY, sizeof(KEY), '\n');
        if (KEY[0] == '.')
        {
            break;
        }
        sol();
    }

    return 0;
}