#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char buf[51];

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int n;
	std::cin >> n;
	int i = 666;
	for (; ; i++)
	{
		int j = i;
		int cnt = 0;
		while (j)
		{
			if (cnt == 3)
			{
				break;
			}

			if (j % 10 == 6)
			{
				cnt++;
			}
			else
			{
				cnt = 0;
			}

			j /= 10;
		}

		if (cnt == 3)
		{
			n--;

			if (n == 0)
			{
				break;
			}
		}
	}

	std::cout << i;


	return 0;
}