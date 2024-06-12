#include <cstdio>

int main(void)
{
    int max = -1;
    int tgt = -1;
    for (int idx = 1; idx <= 9; idx++)
    {
        int num;
        scanf("%d", &num);
        if (num > max)
        {
            max = num;
            tgt = idx;
        }
    }
    printf("%d\n%d", max, tgt);
    return 0;
}