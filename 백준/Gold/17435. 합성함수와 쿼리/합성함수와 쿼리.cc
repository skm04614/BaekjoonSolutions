#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_LOGN = 18;

int PARENT[MAX_LOGN + 1][200200];
int M;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> M;
    for (int i = 1; i <= M; i++)
    {
        std::cin >> PARENT[0][i];
    }

    for (int logn = 1; logn <= MAX_LOGN; logn++)
    {
        for (int i = 1; i <= M; i++)
        {
            PARENT[logn][i] = PARENT[logn - 1][PARENT[logn - 1][i]];
        }
    }

    int N;
    std::cin >> N;
    while (N--)
    {
        int n, lv;
        std::cin >> lv >> n;

        for (int logn = MAX_LOGN; logn >= 0; logn--)
        {
            if (lv >= (1 << logn))
            {
                lv -= (1 << logn);
                n = PARENT[logn][n];
            }
        }
        std::cout << n << '\n';
    }


    return 0;
}