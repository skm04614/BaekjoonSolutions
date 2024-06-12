#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

int T;
int N;
char RECORD[11];

void sol(int snum, int sum, int last_val)
{
	if (snum > N)
	{
		if (sum + last_val == 0)
		{
			std::cout << '1';
			for (int i = 0; i < N - 1; i++)
			{
				std::cout << RECORD[i] << 2 + i;
			}
			std::cout << '\n';
		}

		return;
	}
	
	RECORD[snum - 2] = ' ';
	sol(snum + 1, sum, 10 * last_val + (last_val < 0 ? -snum : snum));

	RECORD[snum - 2] = '+';
	sol(snum + 1, sum + last_val, snum);

	RECORD[snum - 2] = '-';
	sol(snum + 1, sum + last_val, -snum);
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		std::cin >> N;
		sol(2, 0, 1);
		std::cout << '\n';
	}

	return 0;
}