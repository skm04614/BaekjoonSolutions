#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

struct Matrix
{
    ull data[101][101];
    ull N;
    ull modulo;

    Matrix() : Matrix{ 0, 0 }
    {

    }

    Matrix(ull N, ull modulo) : N{ N }, data{}, modulo{ modulo }
    {

    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix ret{ N, modulo };
        for (int i = 0; i < N; i++)
        {
            for (int k = 0; k < N; k++)
            {
                ret.data[i][k] = 0;
                for (int j = 0; j < N; j++)
                {
                    ret.data[i][k] += data[i][j] * other.data[j][k];
                }
                ret.data[i][k] %= modulo;
            }
        }
        return ret;
    }

    void reset(ull N, ull modulo)
    {
        this->N = N;
        this->modulo = modulo;

        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                data[i][j] = 0;
            }
        }
    }
};

Matrix BASE;
Matrix RES;

void sol(ull exponent)
{
    if (exponent == 1)
    {
        RES = BASE;
        return;
    }

    sol(exponent / 2);

    RES = RES * RES;
    if (exponent % 2)
    {
        RES = RES * BASE;
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    ull A, B, C;
    for (;;)
    {
        std::cin >> A >> B >> C;
        if (!A && !B && !C)
        {
            break;
        }

        BASE.reset(A, B);
        RES.reset(A, B);
        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < A; j++)
            {
                std::cin >> BASE.data[i][j];
            }
        }
        
        sol(C);

        for (int i = 0; i < A; i++)
        {
            for (int j = 0; j < A; j++)
            {
                std::cout << RES.data[i][j] % B << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    return 0;
}