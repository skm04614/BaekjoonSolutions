#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

char S[1010];
char T[1010];

int _strlen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

void _str_reverse(char* s)
{
	int len = _strlen(s);

	for (int i = 0; i < (len + 1) / 2; i++)
	{
		char c = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = c;
	}
}

bool _str_eq(const char* s1, const char* s2)
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
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::cin >> S >> T;

	int len_s = _strlen(S);
	int len_t = _strlen(T);

	while (len_s < len_t)
	{
		char c = T[len_t - 1];

		T[len_t - 1] = 0;
		len_t--;

		if (c == 'B')
		{
			_str_reverse(T);
		}
	}

	std::cout << static_cast<int>(_str_eq(S, T));

	return 0;
}