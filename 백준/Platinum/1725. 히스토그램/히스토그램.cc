#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull H[100010];
int N;

int HIDX_STACK[100010];
int SP;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> N;
	ull sol = 0;
	for (int n = 1; n <= N; n++)
	{
		std::cin >> H[n];

		ull x1 = HIDX_STACK[SP];
		while (SP && H[n] < H[HIDX_STACK[SP]])
		{
			ull x0 = HIDX_STACK[SP - 1];
			ull area = (x1 - x0) * H[HIDX_STACK[SP]];
			
			sol = sol > area ? sol : area;

			SP--;
		}

		if (H[n] > H[HIDX_STACK[SP]])
		{
			HIDX_STACK[++SP] = n;
		}
		else
		{
			HIDX_STACK[SP] = n;
		}
	}

	ull x1 = HIDX_STACK[SP];
	while (SP)
	{
		ull x0 = HIDX_STACK[SP - 1];
		ull area = (x1 - x0) * H[HIDX_STACK[SP]];

		sol = sol > area ? sol : area;

		SP--;
	}

	std::cout << sol;

	return 0;
}