#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int ctoi(char c)
{
	if (c <= 'Z')
	{
		return c - 'A';
	}

	return c + 26 - 'a';
}

inline char itoc(int i)
{
	if (i >= 26)
	{
		return i - 26 + 'a';
	}

	return i + 'A';
}

struct Node
{
	Node* child[52];
	bool end;

	Node() : child{}, end{ false }
	{

	}

	~Node()
	{
		for (int i = 0; i < 52; ++i)
		{
			delete child[i];
			child[i] = nullptr;
		}
	}

	bool has_child() const
	{
		for (int i = 0; i < 52; ++i)
		{
			if (child[i])
			{
				return true;
			}
		}

		return false;
	}
};

struct Trie
{
	Node* root;

	Trie() : root{ new Node{} }
	{

	}

	~Trie()
	{
		delete root;
		root = nullptr;
	}

	void insert(const char* s)
	{
		Node* node = root;
		for (; *s; ++s)
		{
			Node*& child = node->child[ctoi(*s)];
			if (child == nullptr)
			{
				child = new Node{};
			}

			node = child;
		}

		node->end = true;
	}

	void remove(const char* s)
	{
		remove(s, root);
	}

	void traverse_print() const
	{
		char buffer[6] = "";
		traverse_print(root, buffer, 0);
	}

private:
	bool remove(const char* s, Node* node)
	{
		if (*s == 0)
		{
			node->end = false;
			return !node->has_child();
		}

		Node*& child = node->child[ctoi(*s)];
		if (child == nullptr)
		{
			return false;
		}

		if (remove(s + 1, child))
		{
			delete child;
			child = nullptr;
			return !node->has_child();
		}

		return false;
	}

	void traverse_print(Node* node, char* buf, int depth) const
	{
		for (int i = 51; i >= 0; --i)
		{
			if (node->child[i] == nullptr)
			{
				continue;
			}

			buf[depth] = itoc(i);
			traverse_print(node->child[i], buf, depth + 1);
		}

		if (node->end)
		{
			buf[depth] = 0;
			std::cout << buf << '\n';
		}
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	std::cout.tie(0);

	char name[6] = "";
	char option[10] = "";

	Trie trie;

	int Q;
	std::cin >> Q;
	while (Q--)
	{
		std::cin >> name >> option;
		if (option[0] == 'e')
		{
			trie.insert(name);
		}
		else
		{
			trie.remove(name);
		}
	}

	trie.traverse_print();

	return 0;
}