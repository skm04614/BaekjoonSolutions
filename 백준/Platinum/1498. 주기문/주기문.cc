#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char KEY[1000100];
int PMATCH[1000100];
int K;

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

void fill_pmatch()
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

            int numerator = i + 1;
            int denominator = (numerator - len);

            if (numerator % denominator == 0 && numerator / denominator > 1)
            {
                std::cout << numerator << ' ' << numerator / denominator << '\n';
            }
        }

        PMATCH[i] = len;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> KEY;
    K = _slen(KEY);
    KEY[K++] = 'X';
    KEY[K] = 0;

    fill_pmatch();


    return 0;
}