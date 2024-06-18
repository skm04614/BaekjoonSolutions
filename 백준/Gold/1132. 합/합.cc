#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

inline int ctoi(char c)
{
    return c - 'A';
}

inline void swap(char& x, char& y)
{
    char tmp = x;
    x = y;
    y = tmp;
}

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

inline void _srev(char* s)
{
    int len = _slen(s);
    for (int i = 0; i < len / 2; ++i)
    {
        swap(s[i], s[len - i - 1]);
    }
}

bool NZERO[10];
ull REC[10];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n;
    char buf[13] = "";
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
    {
        std::cin >> buf;
        NZERO[ctoi(buf[0])] = true;

        _srev(buf);

        ull val = 1;
        for (int j = 0; buf[j]; ++j, val *= 10)
        {
            REC[ctoi(buf[j])] += val;
        }
    }

    ull result = 0;
    int visited = 0;
    {
        ull minimum = 0x7FFFFFFFFFFFFFFF;
        int n = -1;

        for (int c = 0; c < 10; ++c)
        {
            if (NZERO[c])
            {
                continue;
            }

            if (REC[c] < minimum)
            {
                minimum = REC[c];
                n = c;
            }
        }
        visited |= (1 << n);
    }

    for (int multiplier = 1; multiplier < 10; ++multiplier)
    {
        ull minimum = 0x7FFFFFFFFFFFFFFF;
        int n = -1;

        for (int c = 0; c < 10; ++c)
        {
            if (visited & (1 << c))
            {
                continue;
            }

            if (REC[c] < minimum)
            {
                minimum = REC[c];
                n = c;
            }
        }

        visited |= (1 << n);
        result += REC[n] * multiplier;
    }
    std::cout << result;

    return 0;
}
