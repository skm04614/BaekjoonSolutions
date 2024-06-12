#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char S[51];
char T[51];

int slen(const char* s)
{
	int len = 0;
	while (*s++) { len++; }
	return len;
}

bool sol(const char* t, int target_len, const char* s, int idx0, int idx1, bool dir)
{
	if (idx1 - idx0 + 1 == target_len)
	{
		if (dir)
		{
			for (int i = 0; i < target_len; i++)
			{
				if (s[idx0 + i] != t[i])
				{
					return false;
				}
			}
		}
		else
		{
			for (int i = 0; i < target_len; i++)
			{
				if (s[idx1 - i] != t[i])
				{
					return false;
				}
			}
		}

		return true;
	}

	if (dir)
	{
		if (s[idx1] == 'A' && sol(t, target_len, s, idx0, idx1 - 1, dir))
		{
			return true;
		}
		
		if (s[idx0] == 'B' && sol(t, target_len, s, idx0 + 1, idx1, !dir))
		{
			return true;
		}
	}
	else
	{
		if (s[idx0] == 'A' && sol(t, target_len, s, idx0 + 1, idx1, dir))
		{
			return true;
		}

		if (s[idx1] == 'B' && sol(t, target_len, s, idx0, idx1 - 1, !dir))
		{
			return true;
		}
	}

	return false;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);
	std::cin >> T >> S;
	std::cout << static_cast<int>(sol(T, slen(T), S, 0, slen(S) - 1, true));

	return 0;
}