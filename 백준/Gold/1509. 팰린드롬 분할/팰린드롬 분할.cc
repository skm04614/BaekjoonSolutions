#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int UNINITIALIZED = 0x2FFFFFFF;
constexpr int INF = 0X7FFFFFFF;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int s_len(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

char S[2550];
int DP_1[2550][2550];
int DP_2[2550];
int N;

void init()
{
    for (int i = 0; i < N; ++i)
    {
        DP_2[i] = UNINITIALIZED;
        for (int j = 0; j < N; ++j)
        {
            DP_1[i][j] = UNINITIALIZED;
        }
    }
}

int is_palindrome(int idx0, int idx1)
{
    if (idx0 > idx1)
    {
        return 1;
    }

    if (idx0 == idx1)
    {
        return DP_1[idx0][idx0] = 1;
    }

    if (DP_1[idx0][idx1] != UNINITIALIZED)
    {
        return DP_1[idx0][idx1];
    }

    return DP_1[idx0][idx1] = is_palindrome(idx0 + 1, idx1 - 1) && (S[idx0] == S[idx1]);
}

int sol(int idx0, int idx1)
{
    for (int i = idx0; i <= idx1; ++i)
    {
        for (int j = idx0; j <= i; ++j)
        {
            if (is_palindrome(j, i))
            {
                DP_2[i] = min(DP_2[i], DP_2[j - 1] + 1);
            }
        }
    }

    return DP_2[idx1];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> S;
    N = s_len(S);
    init();

    std::cout << sol(0, N - 1);

    return 0;
}
