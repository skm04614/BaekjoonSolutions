#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int H[80080];
int N;

int STACK[80080];
int SP = 0;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> N;
	for (int i = 0; i < N; i++)
	{
		std::cin >> H[i];
	}

	STACK[0] = N;

	unsigned long long sol = 0;
	for (int i = N - 1; i >= 0; i--)
	{
		while (SP && H[STACK[SP]] < H[i])
		{
			--SP;
		}
		STACK[++SP] = i;

		sol += (STACK[SP - 1] - STACK[SP] - 1);
	}
	std::cout << sol;

	return 0;
}