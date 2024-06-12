#include <cstdio>

inline void swap(int &x, int &y)
{
    int t = x;
    x = y;
    y = t;
}

int gcd(int n, int m)
{
    while (n != m)
    {
        if (n > m)
        {
            swap(n, m);
        }
        
        m -= n;
    }
    
    return n;
}

int lcm(int n, int m)
{
    return n * m / gcd(n, m);
}

int main(void)
{
    int n, m;
    scanf("%d %d", &n, &m);
    
    printf("%d\n%d", gcd(n, m), lcm(n, m));
    
    return 0;
}