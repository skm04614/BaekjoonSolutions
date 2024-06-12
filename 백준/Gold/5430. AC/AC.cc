#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char TEST[100010];
int ARR[700010];
int L;
int R;
int D;

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		char c;
		std::cin >> TEST >> R;
		std::cin >> c;
		int cnt = 0;
		for (int i = 0; i < R; i++)
		{
			std::cin >> ARR[i];
			if (++cnt < R)
			{
				std::cin >> c;
			}
		}
		std::cin >> c;

		L = 0;
		D = 1;

		for (const char* ptr = TEST; *ptr; ptr++)
		{
			if (*ptr == 'R')
			{
				D *= -1;
			}
			else
			{
				if (D == -1)
				{
					R--;
				}
				else
				{
					L++;
				}
			}
		}

		if (L > R)
		{
			std::cout << "error";
		}
		else
		{
			int cnt = R - L;
			std::cout << '[';

			if (D == -1)
			{
				for (int i = R - 1; i >= L; i--)
				{
					std::cout << ARR[i];
					if (--cnt)
					{
						std::cout << ',';
					}
				}
			}
			else
			{
				for (int i = L; i < R; i++)
				{
					std::cout << ARR[i];
					if (--cnt)
					{
						std::cout << ',';
					}
				}
			}

			std::cout << ']';
		}

		std::cout << '\n';
	}

	return 0;
}