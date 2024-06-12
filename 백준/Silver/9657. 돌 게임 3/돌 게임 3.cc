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

	int n;
	std::cin >> n;

	DP[1] = 1;
	DP[2] = 0;
	DP[3] = 1;
	DP[4] = 1;

	for (int i = 5; i <= 1000; i++)
	{
		DP[i] = (DP[i - 1] == 0) || (DP[i - 3] == 0) || (DP[i - 4] == 0);
	}

	std::cout << (DP[n] == 1 ? "SK" : "CY");
	 


	return 0;
}