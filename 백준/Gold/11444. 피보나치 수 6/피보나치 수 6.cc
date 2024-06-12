#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <iomanip>

constexpr int MOD = 1000000007;

struct Matrix
{
	unsigned long long data[2][2];

	Matrix operator*(const Matrix& other)
	{
		Matrix ret;

		for (int i = 0; i < 2; i++)
		{
			for (int k = 0; k < 2; k++)
			{
				ret.data[i][k] = 0;
				for (int j = 0; j < 2; j++)
				{
					ret.data[i][k] = (ret.data[i][k] + data[i][j] * other.data[j][k]) % MOD;
				}
			}
		}
		return ret;
	}
};

Matrix ID;
Matrix BASE;
Matrix BASE_SQ;

Matrix pow(unsigned long long exp)
{
	if (exp == 0)
	{
		return ID;
	}

	if (exp == 1)
	{
		return BASE;
	}

	Matrix res = pow(exp / 2);
	res = res * res * pow(exp % 2);
	return res;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	ID.data[0][0] = ID.data[1][1] = 1;

	BASE.data[0][0] = 2;
	BASE.data[0][1] = BASE.data[1][0] = BASE.data[1][1] = 1;

	BASE_SQ = BASE * BASE;

	unsigned long long N;
	std::cin >> N;

	Matrix res = pow((N - 1) / 2);

	std::cout << (res.data[N % 2][0] + res.data[N % 2][1]) % MOD;

	return 0;
}