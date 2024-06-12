#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int CUMSUM[1025][1025];
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int M;
    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            std::cin >> CUMSUM[i][j];
            CUMSUM[i][j] += CUMSUM[i][j - 1] + CUMSUM[i - 1][j] - CUMSUM[i - 1][j - 1];
        }
    }

    while (M--)
    {
        int x1, y1, x2, y2;
        std::cin >> x1 >> y1 >> x2 >> y2;

        --x1;
        --y1;

        int sol = CUMSUM[x2][y2] - CUMSUM[x1][y2] - CUMSUM[x2][y1] + CUMSUM[x1][y1];
        std::cout << sol << '\n';
    }

    return 0;
}