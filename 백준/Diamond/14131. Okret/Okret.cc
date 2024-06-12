#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Node
{
    char ch;

    int size;
    bool flip;

    Node* l;
    Node* r;
    Node* p;

    Node(char ch) : ch{ ch }, size{ 1 }, flip{ false }, l{}, r{}, p{}
    {

    }

    ~Node()
    {
        delete l;
        delete r;
        l = r = nullptr;
    }

    void propagate()
    {
        if (flip)
        {
            swap(l, r);

            if (l)
            {
                l->flip ^= 1;
            }

            if (r)
            {
                r->flip ^= 1;
            }

            flip = false;
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

        p->propagate();
        x->propagate();

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
                return;
            }

            if (g)
            {
                ((x == p->l) == (p == g->l) ? p : x)->rotate();
            }
            x->rotate();
        }
    }
};

struct SplayTree
{
    Node* root;
    int N;

    SplayTree(const char* s) : root{}, N{ 0 }
    {
        root = new Node{ '-' }; // left dummy;

        Node* x = root;
        for (; *s; ++s, ++N)
        {
            x->r = new Node{ *s };
            x->r->p = x;
            x = x->r;
        }

        x->r = new Node{ '+' }; // right dummy
        x->r->p = x;
        x = x->r;

        x->splay();
        root = x;
    }

    ~SplayTree()
    {
        delete root;
        root = nullptr;
    }

    void kth(int k)
    {
        ++k; // compensate for left dummy

        Node* x = root;
        x->propagate();

        for (;;)
        {
            while (x->l && x->l->size >= k)
            {
                x = x->l;
                x->propagate();
            }

            if (x->l)
            {
                k -= x->l->size;
            }

            if (--k == 0)
            {
                break;
            }

            x = x->r;
            x->propagate();
        }

        x->splay();
        root = x;
    }

    Node* gather(int l, int r)
    {
        kth(r + 1);
        Node* tmp = root;
        kth(l - 1);
        tmp->splay(root);

        return root->r->l;
    }

    void flip(int l, int r)
    {
        Node* x = gather(l, r);
        x->flip ^= 1;
    }

    void print()
    {
        for (int i = 1; i <= N; ++i)
        {
            kth(i);
            std::cout << root->ch;
        }
    }
};

char BUF[2500250];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;
    SplayTree stree{ BUF };

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int l, r;
        std::cin >> l >> r;
        stree.flip(l, r);
    }
    stree.print();

    return 0;
}