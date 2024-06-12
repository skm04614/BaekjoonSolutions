#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

char BUF[1001000];
char KEY[1001000];
int K;
int PMATCH[1001000];

int REC[1001000];
int R;

void init_pmatch()
{
    K = _slen(KEY);

    PMATCH[0] = 0;
    int len = 0;
    for (int i = 1; i < K; ++i)
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
}

void find()
{
    int N = _slen(BUF);
    R = 0;

    int len = 0;
    for (int i = 0; i < N; ++i)
    {
        while (len && BUF[i] != KEY[len])
        {
            len = PMATCH[len - 1];
        }

        if (BUF[i] == KEY[len])
        {
            ++len;
        }

        if (len == K)
        {
            REC[++R] = i - len + 2;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin.getline(BUF, sizeof(BUF), '\n');
    std::cin.getline(KEY, sizeof(KEY), '\n');

    init_pmatch();
    find();

    std::cout << R << '\n';
    for (int i = 1; i <= R; ++i)
    {
        std::cout << REC[i] << ' ';
    }

    return 0;
}
