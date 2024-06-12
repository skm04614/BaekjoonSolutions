#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>

struct PTR
{
	char c;
	PTR* prev;
	PTR* next;

	PTR() = default;
	~PTR()
	{
		if (prev)
		{
			prev = nullptr;
			delete prev;
		}
		if (next)
		{
			next = nullptr;
			delete next;
		}
	}

	PTR(char c, PTR* prev, PTR* next)
		: c{ c }, prev{ prev }, next{ next }
	{
	}

	PTR* left()
	{
		return prev ? prev : this;
	}
	
	PTR* right()
	{
		return next ? next : this;
	}

	PTR* insert(char c)
	{
		PTR* newPTR = new PTR{ c, this, next };

		if (next)
		{
			next->prev = newPTR;
		}
		next = newPTR;

		return newPTR;
	}

	PTR* remove()
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
};

char LINE[1000001];
int main(void)
{
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		PTR* head = new PTR{};
		PTR* current = head;
		scanf("%s", LINE);
		for (int i = 0; LINE[i]; i++)
		{
			char c = LINE[i];
			switch (c)
			{
			case '<':
				current = current->left();
				break;
			case '>':
				current = current->right();
				break;
			case '-':
				current = current->remove();
				break;
			default:
				current = current->insert(c);
				break;
			}
		}

		for (current = head->next; current; current = current->next)
		{
			printf("%c", current->c);
		}
		printf("\n");

		delete head;
	}

	return 0;
}