#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { len++; }
    return len;
}

char BUF[1001000];

int sol(const char* buf, int left, int right, int fix_cnt)
{
    if (fix_cnt < 0)
    {
        return 2;
    }

    if (left >= right)
    {
        return fix_cnt ? 0 : 1;
    }

    if (buf[left] == buf[right])
    {
        return sol(buf, left + 1, right - 1, fix_cnt);
    }

    if ((buf[left + 1] == buf[right] && sol(buf, left + 2, right - 1, fix_cnt - 1) == 1)
        || (buf[left] == buf[right - 1] && sol(buf, left + 1, right - 2, fix_cnt - 1) == 1))
    {
        return 1;
    }

    return 2;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> BUF;
        std::cout << sol(BUF, 0, _slen(BUF) - 1, 1) << '\n';
    }
    

    return 0;
}