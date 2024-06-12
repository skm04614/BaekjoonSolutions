#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char TYPES[31][21];
int N[31];
int M;

void _strcpy(char* dest, const char* src)
{
	while (*dest++ = *src++);
}

bool _streq(const char* s1, const char* s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}

	return *s1 == 0 && *s2 == 0;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	int T;
	std::cin >> T;
	for (int t = 0; t < T; t++)
	{
		M = 0;

		int K;
		std::cin >> K;
		for (int k = 0; k < K; k++)
		{
			char unused[21];
			char buf[21];

			std::cin >> unused >> buf;

			int idx = -1;
			for (int m = 0; m < M; m++)
			{
				if (_streq(TYPES[m], buf))
				{
					idx = m;
					N[m]++;
					break;
				}
			}

			if (idx == -1)
			{
				_strcpy(TYPES[M], buf);
				N[M] = 1;
				M++;
			}
		}

		int sol = 1;
		for (int m = 0; m < M; m++)
		{
			sol *= (N[m] + 1);
		}
		std::cout << sol - 1 << '\n';
	}

	return 0;
}