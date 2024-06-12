#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[2002000];
int N;
char KEY[1001000];
int PMATCH[1001000];
int K;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

int gcd(int x, int y)
{
    if (x == y)
    {
        return x;
    }

    if (x > y)
    {
        swap(x, y);
    }

    return gcd(x, y - x);
}

void init_pmatch()
{
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

void sol()
{
    int cnt = 0;
    int mod = 0;
    int len = 0;
    for (int i = 0; i < mod + N; ++i)
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
            ++cnt;
            len = PMATCH[len - 1];
        }
    }

    int _gcd = gcd(cnt, K);

    K /= _gcd;
    cnt /= _gcd;

    std::cout << cnt << '/' << K;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    K = N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> *(BUF + i);
    }
    for (int i = 0; i < N - 1; ++i)
    {
        BUF[N + i] = BUF[i];
    }
    N = 2 * N - 1;

    for (int i = 0; i < K; ++i)
    {
        std::cin >> *(KEY + i);
    }

    init_pmatch();
    sol();

    return 0;
}