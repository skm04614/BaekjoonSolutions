#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int CNT[7];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int i = 1; i <= 6; ++i)
    {
        std::cin >> CNT[i];
    }

    // 6 & 5
    int res = CNT[6] + CNT[5];
    CNT[1] = max(CNT[1] - 11 * CNT[5], 0);

    // 4
    res += CNT[4];
    if (CNT[2] >= 5 * CNT[4])
    {
        CNT[2] -= 5 * CNT[4];
    }
    else
    {
        int tmp = (20 * CNT[4]) - (4 * CNT[2]);
        CNT[1] = max(CNT[1] - tmp, 0);
        CNT[2] = 0;
    }

    // 3
    res += (CNT[3] + 3) / 4;
    if (CNT[3] % 4 == 1)
    {
        CNT[1] = max(CNT[1] - (27 - (4 * min(5, CNT[2]))), 0);
        CNT[2] = max(CNT[2] - 5, 0);
    }
    else if (CNT[3] % 4 == 2)
    {
        CNT[1] = max(CNT[1] - (18 - (4 * min(3, CNT[2]))), 0);
        CNT[2] = max(CNT[2] - 3, 0);
    }
    else if (CNT[3] % 4 == 3)
    {
        CNT[1] = max(CNT[1] - (9 - (4 * min(1, CNT[2]))), 0);
        CNT[2] = max(CNT[2] - 1, 0);
    }

    // 2
    {
        res += (CNT[2] + 8) / 9;
        int tmp = (36 - (4 * (CNT[2] % 9))) % 36;
        CNT[1] = max(CNT[1] - tmp, 0);
    }

    // 1
    res += (CNT[1] + 35) / 36;

    std::cout << res;

    return 0;
}
