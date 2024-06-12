#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char original[110];
char final[300];

char STACK[100][100];
int SP[100];
int S;

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> original;
    
    for (const char *ptr = original; *ptr; ptr++)
    {
        char* stack = STACK[S];
        int& sp = SP[S];

        if (*ptr == '(')
        {
            S++;
        }
        else if (*ptr == ')')
        {
            while (sp)
            {
                std::cout << stack[--sp];
            }
            S--;
        }
        else if (*ptr == '*' || *ptr == '/')
        {
            while (sp && (stack[sp - 1] == '*' || stack[sp - 1] == '/'))
            {
                std::cout << stack[--sp];
            }
            stack[sp++] = *ptr;
        }
        else if (*ptr == '+' || *ptr == '-')
        {
            while (sp)
            {
                std::cout << stack[--sp];
            }
            stack[sp++] = *ptr;
        }
        else
        {
            std::cout << *ptr;
        }
    }

    for (int s = S; s >= 0; s--)
    {
        char* stack = STACK[s];
        int& sp = SP[s];
        while (sp)
        {
            std::cout << stack[--sp];
        }
    }

    return 0;
}