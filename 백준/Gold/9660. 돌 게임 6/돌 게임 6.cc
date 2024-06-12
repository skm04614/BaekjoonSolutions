#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int DP[1010];

int max(int x, int y)
{
	return x > y ? x : y;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	unsigned long long n;
	std::cin >> n;
	n = (n - 1) % 7;
	if (n == 1 || n == 6)
	{
		std::cout << "CY";
	}
	else
	{
		std::cout << "SK";
	}
	 


	return 0;
}