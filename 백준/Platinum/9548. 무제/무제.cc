#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    char chr;
    int size;
    Node* l;
    Node* r;
    Node* p;

    Node(char chr) : chr{ chr }, size{}, l {}, r{}, p{}
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

    void update()
    {
        size = 1 + (l ? l->size : 0) + (r ? r->size : 0);
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

        p->update();
        x->update();
    }

    void splay(Node* target = nullptr)
    {
        Node* x = this;
        while (x->p != target)
        {
            Node* p = x->p;
            Node* g = p->p;
            if (g == target)
            {
                x->rotate();
                break;
            }

            if (g)
            {
                ((x == p->l) == (p == g->l) ? p : x)->rotate();
            }
            x->rotate();
        }
    }

    void traverse_print() const
    {
        if (l)
        {
            l->traverse_print();
        }

        std::cout << chr;

        if (r)
        {
            r->traverse_print();
        }
    }
};

struct SplayTree
{
    Node* root;

    SplayTree(const char* s)
    {
        Node* current = new Node{ '-' };

        while (*s)
        {
            current->r = new Node{ *s++ };
            current->r->p = current;
            current = current->r;
        }

        current->r = new Node{ '+' };
        current->r->p = current;
        current = current->r;

        current->splay();
        root = current;
    }

    ~SplayTree()
    {
        if (root)
        {
            delete root;
            root = nullptr;
        }
    }

    void kth(int k)
    {
        ++k; // count dummy

        Node* current = root;
        for (;;)
        {
            while (current->l && current->l->size >= k)
            {
                current = current->l;
            }

            if (current->l)
            {
                k -= current->l->size;
            }

            if (--k == 0)
            {
                break;
            }

            current = current->r;
        }

        current->splay();
        root = current;
    }

    void insert(int idx0, const char* s)
    {
        Node* sub_tree = new Node{ *s++ };
        while (*s)
        {
            sub_tree->r = new Node{ *s++ };
            sub_tree->r->p = sub_tree;
            sub_tree = sub_tree->r;
        }
        sub_tree->splay();

        kth(idx0);
        Node* right = root->r;

        root->r = sub_tree;
        sub_tree->p = root;

        while (sub_tree->r)
        {
            sub_tree = sub_tree->r;
        }
        sub_tree->r = right;
        right->p = sub_tree;

        right->splay();
        root = right;
    }

    void gather(int idx0, int idx1)
    {
        kth(idx1 + 2);
        Node* tmp = root;
        kth(idx0);
        tmp->splay(root);
    }

    void print(int idx0, int idx1)
    {
        gather(idx0, idx1);
        root->r->l->traverse_print();
        std::cout << '\n';
    }
};


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char* buf = new char[1001000] {};

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> buf;
        SplayTree stree{ buf };
        for (;;)
        {
            std::cin >> buf;
            if (buf[0] == 'E')
            {
                break;
            }

            if (buf[0] == 'I')
            {
                int k;
                std::cin >> buf >> k;
                stree.insert(k, buf);
            }
            else
            {
                int k0, k1;
                std::cin >> k0 >> k1;
                stree.print(k0, k1);
            }
        }
    }

    delete[] buf;

    return 0;
}