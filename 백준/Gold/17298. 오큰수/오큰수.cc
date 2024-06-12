#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[1001000];
int RECORD[1001000];
int N;

int STACK[1001000];
int SP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (register int i = 0; i < N; i++)
    {
        std::cin >> ARR[i];
    }

    for (register int i = N - 1; i >= 0; i--)
    {
        while (SP && STACK[SP] <= ARR[i])
        {
            --SP;
        }

        RECORD[i] = SP ? STACK[SP] : -1;

        STACK[++SP] = ARR[i];
    }

    for (register int i = 0; i < N; i++)
    {
        std::cout << RECORD[i] << ' ';
    }

    return 0;
}