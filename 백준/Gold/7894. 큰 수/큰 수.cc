#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

double RECORD[10000100];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	RECORD[0] = 1;
	for (int n = 1; n <= 10000000; n++)
	{
		RECORD[n] = RECORD[n - 1] + log10(n);
	}

	int T;
	std::cin >> T;
	while (T--)
	{
		int N;
		std::cin >> N;
		std::cout << static_cast<unsigned int>(RECORD[N]) << '\n';
	}

	return 0;
}