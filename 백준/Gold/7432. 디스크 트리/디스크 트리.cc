#include <iostream>

struct Element
{
	char val[90];
	Element* child;
	Element* next;

	Element() : val{}, child{ nullptr }, next{ nullptr }
	{
	}

	Element(const char* val) : Element{}
	{
		for (int idx = 0; val[idx]; idx++)
		{
			this->val[idx] = val[idx];
		}
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
		const char* ptr1 = val;
		const char* ptr2 = other.val;

		while (*ptr1 && *ptr2 && *ptr1 == *ptr2)
		{
			ptr1++;
			ptr2++;
		}

		if (*ptr1 == 0 && *ptr2 == 0)
		{
			return 0;
		}
		
		return *ptr1 > *ptr2 ? 1 : -1;
	}
};

struct Trie
{
	Element root;

	Trie()
	{
		root.child = new Element{};
	}

	void insert(const char* path)
	{
		insert(&root, path);
	}

	void print() const
	{
		print(root.child, 0);
	}

private:
	void insert(Element* current_root, const char* path)
	{
		if (*path == 0)
		{
			return;
		}

		char buf[90] = {};
		for (int idx = 0; *path != 0 && *path != '\\'; idx++, path++)
		{
			buf[idx] = *path;
		}

		if (*path == '\\')
		{
			path++;
		}

		Element* e = new Element{ buf };
		e->child = new Element{};

		Element* child = current_root->child;
		int res = 0;
		while (child->next
			&& (res = child->next->cmp(*e)) == -1)
		{
			child = child->next;
		}

		if (child->next == nullptr)
		{
			child->next = e;
		}
		else if (res == 0)
		{
			delete e;
		}
		else
		{
			e->next = child->next;
			child->next = e;
		}

		insert(child->next, path);
	}

	void print(const Element* current_root, int level) const
	{
		if (current_root->next == nullptr)
		{
			return;
		}

		for (Element* e = current_root->next; e; e = e->next)
		{
			for (int i = 0; i < level; i++)
			{
				std::cout << ' ';
			}
			std::cout << e->val << '\n';
			print(e->child, level + 1);
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
	char buf[90];
	std::cin >> N;
	while (N--)
	{
		std::cin >> buf;
		trie.insert(buf);
	}
	trie.print();

	return 0;
}