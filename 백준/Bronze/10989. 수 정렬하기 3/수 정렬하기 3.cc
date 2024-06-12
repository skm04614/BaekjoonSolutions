#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cmath>

int CNT[10001];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int N;
	std::cin >> N;
	int val;
	for (int i = 0; i < N; i++)
	{
		std::cin >> val;
		CNT[val]++;
	}

	for (int i = 0; i <= 10000; i++)
	{
		while (CNT[i]--)
		{
			std::cout << i << '\n';
		}
	}


	return 0;
}