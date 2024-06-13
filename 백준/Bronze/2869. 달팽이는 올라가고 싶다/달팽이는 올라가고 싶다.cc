#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int A, B, V;
	std::cin >> A >> B >> V;

	V -= A;

	int C = (A - B);

	int sol = (V / C) + (V % C > 0) + 1;
	std::cout << sol;

	return 0;
}