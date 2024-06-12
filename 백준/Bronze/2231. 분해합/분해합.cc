#include <cstdio>

int N;

bool sol(int sum1, int sum2)
{
    if (sum1 + sum2 == N)
    {
        printf("%d", sum1);
        return true;
    }
    
    if (sum1 + sum2 > N)
    {
        return false;
    }
    
    int i0 = sum1 == 0;
    for (int i = i0; i < 10; i++)
    {
        if (sol(10 * sum1 + i, sum2 + i))
        {
            return true;
        }
    }
    
    return false;
}

int main(void)
{
    scanf("%d", &N);
    
    if (!sol(0, 0))
    {
        printf("0");
    }
    
    return 0;
}