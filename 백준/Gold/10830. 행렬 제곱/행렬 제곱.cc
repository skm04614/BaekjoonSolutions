#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Matrix
{
	int data[6][6];
	int N;

	Matrix(int N) : data{}, N{N}
	{

	}

	Matrix operator*(const Matrix& other) const
	{
		Matrix result{ N };
		for (int i = 0; i < N; i++)
		{
			for (int k = 0; k < N; k++)
			{
				result.data[i][k] = 0;
				for (int j = 0; j < N; j++)
				{
					result.data[i][k] = (result.data[i][k] + data[i][j] * other.data[j][k]) % 1000;
				}
			}
		}
		return result;
	}
};

Matrix sol(Matrix base, unsigned long long exponent)
{
	if (exponent == 1)
	{
		return base;
	}

	Matrix result = sol(base, exponent / 2);
	result = result * result;
	if (exponent % 2)
	{
		result = result * base;
	}
	return result;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	unsigned long long M;
	std::cin >> N >> M;
	Matrix base{ N };
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cin >> base.data[i][j];
		}
	}

	Matrix result = sol(base, M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			std::cout << result.data[i][j] % 1000 << ' ';
		}
		std::cout << '\n';
	}

	return 0;
}