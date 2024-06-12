#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

int pow(int base, int exp)
{
    int res = 1;
    while (exp--)
    {
        res *= base;
    }
    return res;
}

char BUF[11][10];
int VAL[11];
int N;

int ARR[0xFF];
int MAP[0xFF];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> BUF[i];

        int len = _slen(BUF[i]);
        int val = pow(10, len - 1);
        for (int j = 0; j < len; ++j, val /= 10)
        {
            ARR[BUF[i][j]] += val;
        }
    }
    
    for (int v = 9; v >= 0; --v)
    {
        int target_c = 'A';
        int max_val = -0x7FFFFFFF;
        for (int c = 'A'; c <= 'Z'; ++c)
        {
            if (ARR[c] > max_val)
            {
                max_val = ARR[c];
                target_c = c;
            }
        }

        ARR[target_c] = -1;
        MAP[target_c] = v;
    }

    int res = 0;
    for (int i = 0; i < N; ++i)
    {
        int len = _slen(BUF[i]);
        int val = pow(10, len - 1);
        for (int j = 0; j < len; ++j, val /= 10)
        {
            res += MAP[BUF[i][j]] * val;
        }
    }
    std::cout << res;


    return 0;
}