#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int a, b, c;
    std::cin >> a >> b >> c;

    std::cout << a + b - c << '\n';

    int n = 1;
    for (n = 1; n <= b; n *= 10);
    std::cout << n * a + b - c;

    return 0;
}
