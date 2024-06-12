#include <cstdio>

int main(void)
{
    int n;
    scanf("%d", &n);
    
    if (n == 1)
    {
       printf("1");
    }
    else
    {
        n--;
        for (int i = 1; ; i++)
        {
            n -= (6 * i);
            if (n <= 0)
            {
                printf("%d", i + 1);
                break;
            }
        }
    }
    
    return 0;
}