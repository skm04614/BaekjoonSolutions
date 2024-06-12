#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int DIFFICULTY[100100];

struct Node
{
	int number;
	Node* l;
	Node* r;
	Node* p;

	Node(int number) : number{ number }, l{}, r{}, p{}
	{

	}

	~Node()
	{
		if (l)
		{
			delete l;
			l = nullptr;
		}

		if (r)
		{
			delete r;
			r = nullptr;
		}
	}

	void rotate()
	{
		Node* x = this;
		Node* p = x->p;

		if (p == nullptr)
		{
			return;
		}

		Node* g = p->p;
		Node* c = nullptr;
		if (x == p->l)
		{
			p->l = c = x->r;
			x->r = p;
		}
		else
		{
			p->r = c = x->l;
			x->l = p;
		}

		x->p = g;
		p->p = x;

		if (c)
		{
			c->p = p;
		}

		if (g)
		{
			(p == g->l ? g->l : g->r) = x;
		}
	}

	void splay()
	{
		register Node* x = this;
		while (x->p)
		{
			register Node* p = x->p;
			register Node* g = p->p;

			if (g)
			{
				((p->l == x) == (g->l == p) ? p : x)->rotate();
			}

			x->rotate();
		}
	}

	int cmp(int number) const
	{
		if (this->number == number)
		{
			return 0;
		}

		if (DIFFICULTY[this->number] == DIFFICULTY[number])
		{
			return this->number < number ? -1 : 1;
		}

		return DIFFICULTY[this->number] < DIFFICULTY[number] ? -1 : 1;
	}
};

struct SplayTree
{
	Node* root;

	SplayTree() : root{}
	{

	}

	~SplayTree()
	{
		if (root)
		{
			delete root;
			root = nullptr;
		}
	}

	void insert(int number)
	{
		if (root == nullptr)
		{
			root = new Node{ number };
			return;
		}

		register Node* current = root;
		for (;;)
		{
			if (current->cmp(number) == 0)
			{
				break;
			}

			if (current->cmp(number) == -1)
			{
				if (current->r == nullptr)
				{
					current->r = new Node{ number };
					current->r->p = current;
				}
				current = current->r;
			}
			else
			{
				if (current->l == nullptr)
				{
					current->l = new Node{ number };
					current->l->p = current;
				}
				current = current->l;
			}
		}

		current->splay();
		root = current;
	}

	bool find(int number)
	{
		if (root == nullptr)
		{
			return false;
		}

		register Node* current = root;
		for (;;)
		{
			if (current->cmp(number) == 0)
			{
				break;
			}

			if (current->cmp(number) == -1)
			{
				if (current->r == nullptr)
				{
					break;
				}
				current = current->r;
			}
			else
			{
				if (current->l == nullptr)
				{
					break;
				}
				current = current->l;
			}
		}

		current->splay();
		root = current;

		return root->number == number;
	}

	void remove(int number)
	{
		if (!find(number))
		{
			return;
		}

		Node* left = root->l;
		Node* right = root->r;
		root->l = root->r = nullptr;
		delete root;
		root = nullptr;

		if (left && right)
		{
			root = left;

			Node* x = root;
			while (x->r)
			{
				x = x->r;
			}
			x->r = right;
			right->p = x;
		}
		else if (left)
		{
			root = left;
		}
		else
		{
			root = right;
		}

		if (root)
		{
			root->p = nullptr;
		}
	}

	int get_lowest()
	{
		if (root == nullptr)
		{
			return -1;
		}

		register Node* current = root;
		while (current->l)
		{
			current = current->l;
		}

		current->splay();
		root = current;

		return current->number;
	}

	int get_highest()
	{
		if (root == nullptr)
		{
			return -1;
		}

		register Node* current = root;
		while (current->r)
		{
			current = current->r;
		}

		current->splay();
		root = current;

		return current->number;
	}
};

int main(void)
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	SplayTree stree;

	int N;
	int course, opt = 0;
	std::cin >> N;
	while (N--)
	{
		std::cin >> course;
		std::cin >> DIFFICULTY[course];
		stree.insert(course);
	}

	char buf[128]{};
	std::cin >> N;
	while (N--)
	{
		std::cin >> buf;
		switch (buf[0])
		{
		case 'a':
			std::cin >> course;
			std::cin >> DIFFICULTY[course];
			stree.insert(course);
			break;
		case 's':
			std::cin >> course;
			stree.remove(course);
			break;
		default:
			std::cin >> opt;
			if (opt == 1)
			{
				std::cout << stree.get_highest() << '\n';
			}
			else
			{
				std::cout << stree.get_lowest() << '\n';
			}
			break;
		}
	}

	return 0;
}