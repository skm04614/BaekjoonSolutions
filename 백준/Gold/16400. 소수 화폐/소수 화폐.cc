#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

using ull = unsigned long long;
ull DP[2][40001];

ull PRIMES[40001];
ull P;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	for (int n = 2; n <= 40000; n++)
	{
		bool is_prime = true;
		for (int i = 2; i <= sqrt(n); i++)
		{
			if (n % i == 0)
			{
				is_prime = false;
				break;
			}
		}

		if (is_prime)
		{
			PRIMES[P++] = n;
		}
	}

	int price;
	std::cin >> price;

	int p = 0;
	int c = 1;
	for (int i = 0; i < P; i++)
	{
		const ull& coin = PRIMES[i];
		for (ull v = 0; v < coin; v++)
		{
			DP[c][v] = (DP[p][v]) % 123456789;
		}

		DP[c][coin] = (DP[p][coin] + 1) % 123456789;

		for (ull v = coin + 1; v <= 40000; v++)
		{
			DP[c][v] = (DP[p][v] + DP[c][v - coin]) % 123456789;
		}

		p ^= 1;
		c ^= 1;
	}
	std::cout << DP[p][price];


	return 0;
}