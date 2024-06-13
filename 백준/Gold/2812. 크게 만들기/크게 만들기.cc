#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int STACK[500500];
int SP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, K;
    std::cin >> N >> K;
    for (int i = 0; i < N; ++i)
    {
        char c;
        std::cin >> c;

        int val = c - '0';
        while (K && SP && STACK[SP] < val)
        {
            --SP;
            --K;
        }
        STACK[++SP] = val;
    }

    while (K && SP)
    {
        --SP;
        --K;
    }

    for (int i = 1; i <= SP; ++i)
    {
        std::cout << STACK[i];
    }


    return 0;
}