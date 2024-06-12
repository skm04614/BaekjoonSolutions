#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

struct Matrix
{
	ull data[8][8];

	Matrix() : data{}
	{

	}

	Matrix operator*(const Matrix& other) const
	{
		Matrix ret{};

		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				ret.data[i][j] = 0;
				for (int k = 0; k < 8; k++)
				{
					ret.data[i][j] = (ret.data[i][j] + data[i][k] * other.data[k][j]) % MOD;
				}
			}
		}

		return ret;
	}
};

Matrix ID;

Matrix pow(Matrix base, int exp)
{
	if (exp == 0)
	{
		return ID;
	}
	if (exp == 1)
	{
		return base;
	}

	Matrix tmp = pow(base, exp / 2);
	return tmp * tmp * pow(base, exp % 2);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	Matrix base{};
	
	base.data[0][1] = base.data[1][0] = 1; // 학생회관 - 진리관
	base.data[0][2] = base.data[2][0] = 1; // 학생회관 - 형남공학관
	base.data[1][4] = base.data[4][1] = 1; // 진리관 - 한경직기념관
	base.data[2][4] = base.data[4][2] = 1; // 형남공학관 - 한경직기념관
	base.data[1][3] = base.data[3][1] = 1; // 진리관 - 신양관
	base.data[3][4] = base.data[4][3] = 1; // 신양관 - 한경직기념관
	base.data[3][6] = base.data[6][3] = 1; // 신양관 - 미래관
	base.data[4][6] = base.data[6][4] = 1; // 한경직기념관 - 미래관
	base.data[3][5] = base.data[5][3] = 1; // 신양관 - 전산관
	base.data[5][6] = base.data[6][5] = 1; // 전산관 - 미래관
	base.data[5][7] = base.data[7][5] = 1; // 전산관 - 정보과학관
	base.data[6][7] = base.data[7][6] = 1; // 미래관 - 정보과학관

	for (int i = 0; i < 8; i++)
	{
		ID.data[i][i] = 1;
	}
	
	int exponent;
	std::cin >> exponent;
	Matrix result = pow(base, exponent);

	std::cout << result.data[7][7];

	return 0;
}