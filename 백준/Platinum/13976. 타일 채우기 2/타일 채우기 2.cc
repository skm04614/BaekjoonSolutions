#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

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
                    ret.data[i][k] = (ret.data[i][k] + data[i][j] * other.data[j][k] + MOD) % MOD;
                }
            }
        }

        return ret;
    }
};

Matrix BASE;
Matrix ID;

Matrix _pow(ull exponent)
{
    if (exponent == 0)
    {
        return ID;
    }

    if (exponent == 1)
    {
        return BASE;
    }

    Matrix ret = _pow(exponent / 2);
    return ret * ret * _pow(exponent % 2);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    ID.data[0][0] = ID.data[1][1] = 1;

    BASE.data[0][0] = 4;
    BASE.data[0][1] = -1;
    BASE.data[1][0] = 1;
    BASE.data[1][1] = 0;

    ull N;
    std::cin >> N;
    if (N % 2)
    {
        std::cout << 0;
    }
    else
    {
        ull exp = (N - 1) / 2;
        Matrix res = _pow(exp);
        std::cout << (res.data[0][0] * 3 + res.data[0][1] * 1 + MOD) % MOD;
    }

    return 0;
}