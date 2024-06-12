#include <iostream>

struct Node
{
    char chr;
    int size;

    Node* l;
    Node* r;
    Node* p;

    Node(char chr) : size{ 1 }, chr{ chr }, l{}, r{}, p{}
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
        size = 1;

        if (l)
        {
            size += l->size;
        }

        if (r)
        {
            size += r->size;
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

        p->p = x;
        x->p = g;

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

    void splay(Node* tgt = nullptr)
    {
        Node* x = this;
        while (x->p != tgt)
        {
            Node* p = x->p;
            Node* g = p->p;
            if (g == tgt)
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
        _traverse_print();
        std::cout << '\n';
    }

    void _traverse_print() const
    {
        if (l)
        {
            l->_traverse_print();
        }

        std::cout << chr;

        if (r)
        {
            r->_traverse_print();
        }
    }
};

struct SplayTree
{
    Node* root;

    SplayTree(const char* s) : root{}
    {
        root = new Node{ '-' };
        Node* current = root;
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
        ++k; // left dummy

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

    void insert(char chr, int idx)
    {
        kth(idx);

        Node* subtree = root->l;
        Node* x = new Node{ chr };

        root->l = subtree->p = x;
        x->p = root;
        x->l = subtree;

        subtree->splay();
        root = subtree;
    }

    void gather(int idx0, int idx1)
    {
        kth(idx1 + 1);
        Node* tmp = root;
        kth(idx0 - 1);
        tmp->splay(root);
    }

    void remove_and_print(int idx0, int idx1)
    {
        gather(idx0, idx1);

        Node* x = root->r;
        Node* rmv = x->l;
        x->l = nullptr;

        rmv->traverse_print();
        delete rmv;

        x->splay();
        root = x;
    }
};


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    char* buf = new char[300300]{};
    std::cin >> buf;

    SplayTree stree{ buf };
    delete[] buf;

    while (M--)
    {
        int opt;
        std::cin >> opt;
        if (opt == 1)
        {
            char chr;
            int idx;
            std::cin >> chr >> idx;
            stree.insert(chr, idx);
        }
        else
        {
            int idx0, idx1;
            std::cin >> idx0 >> idx1;
            stree.remove_and_print(idx0, idx1);
        }
    }

    return 0;
}
