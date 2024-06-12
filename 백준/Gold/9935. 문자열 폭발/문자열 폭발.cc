#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Stack
{
	char data[1000001] = {};
	int sp = 0;

	void push(const char c)
	{
		data[sp++] = c;
	}

	void popIfAllowed(const char* substr, int len)
	{
		if (sp < len)
		{
			return;
		}

		for (int i = 0; i < len; i++)
		{
			if (data[sp - len + i] != substr[i])
			{
				return;
			}
		}

		sp -= len;
	}

	bool empty() const
	{
		return sp == 0;
	}

	void print_result()
	{
		data[sp] = 0;

		if (sp)
		{
			std::cout << data;
		}
		else
		{
			std::cout << "FRULA";
		}
	}
};


char word[1000001];
char bomb[37];

Stack STACK;

int _strlen(const char* str)
{
	int len = 0;
	for (; *str; len++, str++);
	return len;
}

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(nullptr);
	std::cout.tie(nullptr);

	std::cin >> word >> bomb;

	int wlen = _strlen(word);
	int blen = _strlen(bomb);

	for (int i = 0; i < wlen; i++)
	{
		STACK.push(word[i]);
		STACK.popIfAllowed(bomb, blen);
	}
	STACK.print_result();

	return 0;
}