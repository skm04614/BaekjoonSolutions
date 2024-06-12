#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <cmath>


int ARR[20000010];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n, m;
	std::cin >> n;
	int val;
	for (int i = 0; i < n; i++)
	{
		std::cin >> val;
		val += 10000000;

		ARR[val]++;
	}

	std::cin >> m;
	for (int i = 0; i < m; i++)
	{
		std::cin >> val;
		val += 10000000;
		std::cout << ARR[val] << ' ';
	}


	return 0;

}