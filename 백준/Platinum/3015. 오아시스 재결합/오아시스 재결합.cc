#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int H[500500];
int N;

struct Element
{
    int h;
    int cnt;
};

Element STACK[500500];
int SP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (register int i = 1; i <= N; i++)
    {
        std::cin >> H[i];
    }

    unsigned long long sol = 0;
    for (register int i = 1; i <= N; i++)
    {
        while (SP && STACK[SP].h < H[i])
        {
            sol += STACK[SP--].cnt;
        }

        if (STACK[SP].h == H[i])
        {
            sol += STACK[SP].cnt++;

            if (SP - 1)
            {
                ++sol;
            }
        }
        else
        {
            if (SP)
            {
                ++sol;
            }

            STACK[++SP] = { H[i], 1 };
        }
    }
    std::cout << sol;


    return 0;
}