#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


char RECORD[10000][20010];
int CNT[10000];
int Q[10000];

int L;
int R;
int START;
int END;

void init()
{
	for (int i = 0; i < 10000; i++)
	{
		CNT[i] = 0;
	}
	std::cin >> START >> END;

	L = -1;
	R = -1;
	Q[++R] = START;
	RECORD[START][0] = 0;
}

void _strcpy(char* dest, char* src)
{
	while (*dest++ = *src++);
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
		init();

		while (L != R)
		{
			int current_val = Q[++L];

			if (current_val == END)
			{
				std::cout << RECORD[current_val] << '\n';
				break;
			}

			for (int i = 0; i < 4; i++)
			{
				int new_val = 0;
				char op = 0;
				switch (i)
				{
				case 0:
					new_val = (2 * current_val) % 10000;
					op = 'D';
					break;
				case 1:
					new_val = (9999 + current_val) % 10000;
					op = 'S';
					break;
				case 2:
					new_val = (10 * (current_val % 1000)) + (current_val / 1000);
					op = 'L';
					break;
				default:
					new_val = (1000 * (current_val % 10)) + (current_val / 10);
					op = 'R';
					break;
				}

				if (new_val != START && CNT[new_val] == 0)
				{
					CNT[new_val] = CNT[current_val] + 1;
					_strcpy(RECORD[new_val], RECORD[current_val]);
					RECORD[new_val][CNT[current_val]] = op;
					RECORD[new_val][CNT[new_val]] = 0;
					Q[++R] = new_val;
				}
			}
		}
	}

	return 0;
}