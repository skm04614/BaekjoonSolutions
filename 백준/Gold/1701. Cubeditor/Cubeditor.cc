#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { len++; }
    return len;
}

char S[5050];
int PMATCH[5050];
int N;

void clear_pmatch()
{
    for (int i = 0; i < N; ++i)
    {
        PMATCH[i] = 0;
    }
}

void sol()
{
    int res = 0;

    for (int i = 0; i < N; ++i)
    {
        clear_pmatch();
        const char* ptr = S + i;

        PMATCH[0] = 0;
        int len = 0;
        for (int j = 1; j < N - i; ++j)
        {
            while (len && ptr[len] != ptr[j])
            {
                len = PMATCH[len - 1];
            }

            if (ptr[j] == ptr[len])
            {
                ++len;
            }

            res = res > len ? res : len;
            PMATCH[j] = len;
        }
    }
    std::cout << res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> S;
    N = _slen(S);
    sol();

    return 0;
}