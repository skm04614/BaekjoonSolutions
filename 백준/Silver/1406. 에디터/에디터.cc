#include <cstdio>
#include <iostream>

struct PTR
{
	char c;
	PTR* next;
	PTR* prev;

	~PTR()
	{
		if (prev)
		{
			prev->next = nullptr;
			delete prev;
		}
		if (next)
		{
			next->prev = nullptr;
			delete next;
		}
	}

	PTR* insert(char c)
	{
		PTR* newPTR = new PTR{ c, next, this };
		if (next)
		{
			next->prev = newPTR;
		}
		next = newPTR;
		return newPTR;
	}

	PTR* del()
	{
		if (!prev)
		{
			return this;
		}

		prev->next = next;
		if (next)
		{
			next->prev = prev;
		}

		PTR* tmp = prev;

		prev = next = nullptr;

		return tmp;
	}

	PTR* left()
	{
		return prev ? prev : this;
	}

	PTR* right()
	{
		return next ? next : this;
	}
};


char initial[100010];

int main(void)
{
	PTR* head = new PTR{};
	PTR* current = head;

	std::cin >> initial;
	for (int i = 0; initial[i]; i++)
	{
		current = current->insert(initial[i]);
	}

	int m;
	char x;
	std::cin >> m;
	while (m--)
	{
		std::cin >> x;
		switch (x)
		{
		case 'L':
			current = current->left();
			break;
		case 'D':
			current = current->right();
			break;
		case 'B':
			current = current->del();
			break;
		case 'P':
			std::cin >> x;
			current = current->insert(x);
			break;
		}
	}

	for (current = head->next; current; current = current->next)
	{
		printf("%c", current->c);
	}

	delete head;
	return 0;
}