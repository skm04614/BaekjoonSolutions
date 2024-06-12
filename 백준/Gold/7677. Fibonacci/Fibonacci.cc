#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

struct Matrix
{
    ull data[2][2];

    Matrix() : data{}
    {

    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix ret;
        for (int i = 0; i < 2; i++)
        {
            for (int k = 0; k < 2; k++)
            {
                ret.data[i][k] = 0;
                for (int j = 0; j < 2; j++)
                {
                    ret.data[i][k] = (ret.data[i][k] + data[i][j] * other.data[j][k]) % 10000;
                }
            }
        }
        return ret;
    }
};

Matrix ID;
Matrix BASE;

Matrix _pow(ull exp)
{
    if (exp == 0)
    {
        return ID;
    }

    if (exp == 1)
    {
        return BASE;
    }

    Matrix ret = _pow(exp / 2);
    return ret * ret * _pow(exp % 2);
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    ID.data[0][0] = ID.data[1][1] = 1;
    BASE.data[0][0] = 1;
    BASE.data[0][1] = 1;
    BASE.data[1][0] = 1;
    BASE.data[1][1] = 0;

    for (;;)
    {
        int N;
        std::cin >> N;
        if (N == -1)
        {
            break;
        }

        if (N == 0)
        {
            std::cout << 0 << '\n';
        }
        else
        {
            Matrix ret = _pow(N - 1);
            std::cout << ret.data[0][0] << '\n';
        }
    }

    return 0;
}