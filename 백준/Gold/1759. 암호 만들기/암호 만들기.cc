#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char PW[16];
char POOL[16];
int L;
int C;

void _insertion_sort(char* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		int _i = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[j] < arr[_i])
			{
				_i = j;
			}
		}

		char tmp = arr[_i];
		arr[_i] = arr[i];
		arr[i] = tmp;
	}
}

void sol(int sidx, int depth, int vowel_cnt, int non_vowel_cnt)
{
	if (depth == L)
	{
		if (vowel_cnt >= 1 && non_vowel_cnt >= 2)
		{
			std::cout << PW << '\n';
		}
		return;
	}

	for (int i = sidx; i < C; i++)
	{
		const char& c = POOL[i];
		bool is_vowel = (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
		PW[depth] = c;
		sol(i + 1, depth + 1, vowel_cnt + is_vowel, non_vowel_cnt + !is_vowel);
	}
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> L >> C;
	for (int i = 0; i < C; i++)
	{
		std::cin >> POOL[i];
	}
	_insertion_sort(POOL, C);
	sol(0, 0, 0, 0);


	return 0;
}