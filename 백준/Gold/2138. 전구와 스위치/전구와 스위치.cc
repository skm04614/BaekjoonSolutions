#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ORIGINAL[2][100100];
int TARGET[100100];
int N;

int _switch(int i, int n)
{
    if (n == 0)
    {
        ORIGINAL[i][0] ^= 1;
        ORIGINAL[i][1] ^= 1;
    }
    else if (n == N - 1)
    {
        ORIGINAL[i][N - 1] ^= 1;
        ORIGINAL[i][N - 2] ^= 1;
    }
    else
    {
        ORIGINAL[i][n - 1] ^= 1;
        ORIGINAL[i][n] ^= 1;
        ORIGINAL[i][n + 1] ^= 1;
    }

    return 1;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    char c;
    for (int i = 0; i < N; i++)
    {
        std::cin >> c;
        for (int j = 0; j < 2; j++)
        {
            ORIGINAL[j][i] = c - '0';
        }
    }

    for (int i = 0; i < N; i++)
    {
        std::cin >> c;
        TARGET[i] = c - '0';
    }

    int sol[2] = {};
    sol[1] += _switch(1, 0);

    for (int i = 1; i < N; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (ORIGINAL[j][i - 1] != TARGET[i - 1])
            {
                sol[j] += _switch(j, i);
            }
        }
    }

    int _sol = 0x7FFFFFFF;
    for (int j = 0; j < 2; j++)
    {
        bool is_valid = true;
        for (int i = 0; i < N; i++)
        {
            if (ORIGINAL[j][i] != TARGET[i])
            {
                is_valid = false;
                break;
            }
        }
        
        if (is_valid)
        {
            _sol = _sol < sol[j] ? _sol : sol[j];
        }
    }
    std::cout << (_sol == 0x7FFFFFFF ? -1 : _sol);


    return 0;
}