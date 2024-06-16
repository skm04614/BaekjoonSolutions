#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char BUF[110];
int CNT[27];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> BUF;
    for (int i = 0; BUF[i]; ++i)
    {
        CNT[BUF[i] - 'a']++;
    }

    for (int i = 0; i < 26; ++i)
    {
        std::cout << CNT[i] << ' ';
    }

    return 0;
}
