#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int max(int n, int m)
{
	return n > m ? n : m;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int n;
	std::cin >> n;

	int v = n;
	int sol = 0;
	do
	{
		v = ((v % 10) * 10) + (((v / 10) + (v % 10)) % 10);
		sol++;
	} while (v != n);
	std::cout << sol;

	return 0;
}