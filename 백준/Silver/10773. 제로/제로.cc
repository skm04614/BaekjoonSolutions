#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int STACK[100010];
int SP = 0;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);
	
	int K;
	std::cin >> K;

	int val;
	for (int i = 0; i < K; i++)
	{
		std::cin >> val;
		if (val)
		{
			STACK[SP++] = val;
		}
		else
		{
			SP--;
		}
	}
	
	int sum = 0;
	for (int i = 0; i < SP; i++)
	{
		sum += STACK[i];
	}

	std::cout << sum;

	return 0;
}