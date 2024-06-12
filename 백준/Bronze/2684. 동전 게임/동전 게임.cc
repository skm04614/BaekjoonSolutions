#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 



inline void swap(int& n, int& m)
{
	int tmp = n;
	n = m;
	m = tmp;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	int N;
	std::cin >> N;

	char c;
	for (int n = 0; n < N; n++)
	{
		int record[2][2][2] = {};

		std::cin >> c;
		int i = (c == 'H');
		std::cin >> c;
		int j = (c == 'H');
		for (int x = 0; x < 38; x++)
		{
			std::cin >> c;
			int k = (c == 'H');

			record[i][j][k]++;

			swap(j, k);
			swap(i, k);
		}

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				for (int k = 0; k < 2; k++)
				{
					std::cout << record[i][j][k] << ' ';
				}
			}
		}
		std::cout << '\n';
	}
	
	return 0;
}