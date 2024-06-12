#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

struct Matrix
{
	ull data[51][51];
	int N;

	Matrix() : data{}
	{

	}

	void set_dimension(int N)
	{
		this->N = N;
	}

	Matrix& operator*=(const Matrix& other)
	{
		Matrix* ret = new Matrix{};
		ret->set_dimension(N);

		for (int i = 1; i <= N; i++)
		{
			for (int j = 1; j <= N; j++)
			{
				ret->data[i][j] = 0;
				for (int k = 1; k <= N; k++)
				{
					ret->data[i][j] = (ret->data[i][j] + data[i][k] * other.data[k][j]) % MOD;
				}
			}
		}

		*this = *ret;

		delete ret;

		return *this;
	}
};

Matrix BASE;
Matrix ID;
Matrix RES;

void _pow(int exp)
{
	if (exp == 0)
	{
		RES *= ID;
		return;
	}

	if (exp == 1)
	{
		RES *= BASE;
		return;
	}

	_pow(exp / 2);

	RES *= RES;

	_pow(exp % 2);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N, M;
	std::cin >> N >> M;
	BASE.set_dimension(N);
	ID.set_dimension(N);

	for (int i = 1; i <= M; i++)
	{
		int src, dest;
		std::cin >> src >> dest;

		BASE.data[src][dest] = BASE.data[dest][src] = 1;
	}

	for (int i = 1; i <= N; i++)
	{
		ID.data[i][i] = 1;
	}

	RES = ID;
	
	int exponent;
	std::cin >> exponent;
	_pow(exponent);

	std::cout << RES.data[1][1];

	return 0;
}