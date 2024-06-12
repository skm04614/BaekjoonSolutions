#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[2][5050];
int N[2];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N[0];
    std::cin >> ARR[0][0];
    for (int i = 0; i < N[0] - 1; ++i)
    {
        std::cin >> ARR[0][i];
        --ARR[0][i];
    }

    int sol = 0;
    for (int i = 0; ; i = (i + 1) & 1)
    {
        const int* current = ARR[i];
        const int& n = N[i];
        if (n == 0)
        {
            break;
        }

        const int base = current[0];

        int* next = ARR[(i + 1) & 1];
        int& m = N[(i + 1) & 1] = 0;
        
        for (int i = 0; i < n; ++i)
        {
            if (current[i] % current[0])
            {
                next[m++] = current[i];
            }
        }

        ++sol;
    }
    std::cout << sol;

    return 0;
}