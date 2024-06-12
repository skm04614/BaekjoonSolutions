#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;
ull H[100010];
int N;

ull STACK[100010];
ull SP;
ull SOL;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	for (;;)
	{
		SP = 0;
		SOL = 0;

		std::cin >> N;
		if (N == 0)
		{
			break;
		}

		for (int i = 1; i <= N; i++)
		{
			std::cin >> H[i];

			ull x1 = STACK[SP];
			while (SP > 0 && H[i] < H[STACK[SP]])
			{
				ull l = x1 - STACK[SP - 1];
				ull h = H[STACK[SP]];
				ull area = l * h;

				SOL = SOL > area ? SOL : area;

				SP--;
			}

			if (SP == 0 || H[i] > H[STACK[SP]])
			{
				STACK[++SP] = i;
			}
			else if (H[i] == H[STACK[SP]])
			{
				STACK[SP] = i;
			}
		}

		ull x1 = STACK[SP];
		while (SP > 0)
		{
			ull l = x1 - STACK[SP - 1];
			ull h = H[STACK[SP]];
			ull area = l * h;

			SOL = SOL > area ? SOL : area;

			SP--;
		}

		std::cout << SOL << '\n';
	}


	return 0;
}