#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int N;
int ARR[1001000];
int PMATCH[1001000];

void fill_pmatch()
{
    PMATCH[0] = 0;

    int len = 0;
    for (int i = 1; i < N; i++)
    {
        while (len && ARR[i] != ARR[len])
        {
            len = PMATCH[len - 1];
        }

        if (ARR[i] == ARR[len])
        {
            ++len;
        }

        PMATCH[i] = len;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int n = N - 1; n >= 0; n--)
    {
        std::cin >> ARR[n];
    }

    fill_pmatch();

    int max_val = 0;
    int max_cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (PMATCH[i] > max_val)
        {
            max_val = PMATCH[i];
            max_cnt = 1;
        }
        else if (PMATCH[i] == max_val)
        {
            ++max_cnt;
        }
    }

    if (max_val == 0)
    {
        std::cout << -1;
    }
    else
    {
        std::cout << max_val << ' ' << max_cnt;
    }

    return 0;
}