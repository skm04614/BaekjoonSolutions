#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[500500];
int REC[500500];
int N;

int STACK[500500];
int SP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (register int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i];
    }

    for (register int i = N; i >= 1; i--)
    {
        while (SP && ARR[i] >= ARR[STACK[SP]])
        {
            REC[STACK[SP--]] = i;
        }

        STACK[++SP] = i;
    }
    
    for (register int i = 1; i <= N; i++)
    {
        std::cout << REC[i] << ' ';
    }

    return 0;
}