#include <cstdio>
#include <iostream>

int pow(int n, int m)
{
	if (m == 0)
	{
		return 1;
	}
	
	return n * pow(n, m - 1);
}

void hanoi(int n, int src = 1, int tmp = 2, int dest = 3)
{
	if (n == 0)
	{
		return;
	}

	hanoi(n - 1, src, dest, tmp);
	printf("%d %d\n", src, dest);
	hanoi(n - 1, tmp, src, dest);
}

int main(void)
{
	int n;
	std::cin >> n;

	std::cout << pow(2, n) - 1 << std::endl;
	hanoi(n);

	return 0;
}