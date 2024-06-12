#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;
    
    int res = 0;
    while (n)
    {
        res += n & 1;
        n >>= 1;
    }
    std::cout << res;

    return 0;
}
