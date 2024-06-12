#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char BUF[1000100];

char STACK[1000100];
int SP;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;

    for (int i = 0; BUF[i]; i++)
    {
        STACK[SP++] = BUF[i];

        for (; SP >= 4;)
        {
            if (STACK[SP - 1] == 'P'
                && STACK[SP - 2] == 'A'
                && STACK[SP - 3] == 'P'
                && STACK[SP - 4] == 'P')
            {
                SP -= 3;
            }
            else
            {
                break;
            }
        }
    }


    std::cout << ((SP == 1 && STACK[0] == 'P') ? "PPAP" : "NP");

    return 0;
}