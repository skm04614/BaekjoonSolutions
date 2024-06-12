#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

struct Matrix
{
    ull val[21][21];
    int N;

    Matrix() : val{}
    {

    }

    Matrix operator*(const Matrix& other) const
    {
        Matrix ret{};
        ret.N = N;

        for (int k = 1; k <= N; k++)
        {
            for (int i = 1; i <= N; i++)
            {
                for (int j = 1; j <= N; j++)
                {
                    ret.val[i][j] = (ret.val[i][j] + val[i][k] * other.val[k][j]) % MOD;
                }
            }
        }

        return ret;
    }

    void print() const
    {
        for (int i = 1; i <= N; i++)
        {
            for (int j = 1; j <= N; j++)
            {
                std::cout << val[i][j] << ' ';
            }
            std::cout << '\n';
        }
    }
};

Matrix BASES[101];
int T;
Matrix SOL;

Matrix pow(int exp)
{
    if (exp == 0)
    {
        return BASES[0];
    }
    
    if (exp == 1)
    {
        return BASES[T];
    }

    Matrix tmp = pow(exp / 2);
    tmp = tmp * tmp * pow(exp % 2);

    return tmp;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    int D;
    std::cin >> T >> N >> D;

    BASES[0].N = N;
    for (int i = 1; i <= N; i++)
    {
        BASES[0].val[i][i] = 1;
    }

    for (int t = 1; t <= T; t++)
    {
        Matrix& base = BASES[t];

        base.N = N;

        int cnt;
        std::cin >> cnt;
        while (cnt--)
        {
            int a, b, c;
            std::cin >> a >> b >> c;
            base.val[a][b] = c;
        }

        base = BASES[t - 1] * base;
    }

    int exp = D / T;
    int quotient = D % T;

    Matrix res = pow(exp) * BASES[quotient];
    res.print();

    return 0;
}