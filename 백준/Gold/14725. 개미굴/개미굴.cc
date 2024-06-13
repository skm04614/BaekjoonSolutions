#define _CRT_SECURE_NO_WARNINGS

#include <iostream> 

struct Element
{
	char val[20];
	Element* next;
	Element* child;

	Element() : val{}, next{}, child{}
	{
	}

	Element(const char* val) : Element{}
	{
		char* ptr = this->val;
		while (*ptr++ = *val++);
	}

	~Element()
	{
		if (next)
		{
			delete next;
		}

		if (child)
		{
			delete child;
		}
	}

	int cmp(const Element& other) const
	{
		const char* s1 = val;
		const char* s2 = other.val;

		while (*s1 && *s2 && *s1 == *s2)
		{
			s1++;
			s2++;
		}

		if (*s1 == 0 && *s2 == 0)
		{
			return 0;
		}

		return *s1 > *s2 ? 1 : -1;
	}

	static Element* create(const char* s)
	{
		Element* ret = new Element{ s };
		ret->child = new Element{};

		return ret;
	}
};

struct Trie
{
	Trie() : root{Element::create("")}
	{
	}

	~Trie()
	{
		delete root;
	}

	void insert(const char(*input)[20], int size)
	{
		insert(root, input, 0, size);
	}

	void print() const
	{
		print(root->child, 0);
	}

private:
	Element* const root;

	void insert(Element* current_root, const char(*input)[20], int idx, const int size)
	{
		if (idx == size)
		{
			return;
		}

		Element* e = Element::create(input[idx]);

		Element* child = current_root->child;
		if (child->next == nullptr)
		{
			child->next = e;
		}
		else
		{
			int res = 0;
			while (child->next && (res = e->cmp(*(child->next))) == 1)
			{
				child = child->next;
			}

			if (res == 0)
			{
				delete e;
			}
			else
			{
				e->next = child->next;
				child->next = e;
			}
		}

		insert(child->next, input, idx + 1, size);
	}

	void print(const Element* current_root, int level) const
	{
		if (current_root == nullptr)
		{
			return;
		}

		for (const Element* node = current_root->next; node; node = node->next)
		{
			for (int i = 0; i < 2 * level; i++)
			{
				std::cout << '-';
			}
			std::cout << node->val << '\n';
			print(node->child, level + 1);
		}
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	Trie trie;

	int N;
	std::cin >> N;

	int size;
	char input[15][20];
	for (int i = 0; i < N; i++)
	{
		std::cin >> size;
		for (int j = 0; j < size; j++)
		{
			std::cin >> input[j];
		}
		trie.insert(input, size);
	}
	trie.print();

	return 0;
}