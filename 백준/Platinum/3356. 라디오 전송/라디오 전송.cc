#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

char KEY[1001000];
int PMATCH[1001000];
int K;

void sol(void)
{
    std::cin >> K >> KEY;

    PMATCH[0] = 0;

    int len = 0;
    for (int i = 1; i < K; i++)
    {
        while (len && KEY[len] != KEY[i])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[len] == KEY[i])
        {
            ++len;
        }

        PMATCH[i] = len;
    }

    std::cout << K - PMATCH[K - 1];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    sol();

    return 0;
}