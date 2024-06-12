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

    Node* l;
    Node* r;
    Node* p;

    Node(char ch) : ch{ ch }, size{ 1 }, l{}, r{}, p{}
    {

    }

    ~Node()
    {
        delete l;
        delete r;
        l = r = nullptr;
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
                return;
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

        std::cout << ch;

        if (r)
        {
            r->traverse_print();
        }
    }
};

struct SplayTree
{
    Node* root;

    SplayTree()
    {
        Node* x = root = new Node{ 1 }; // left dummy
        x->r = new Node{ 2 }; // right dummy
        x->r->p = x;
        x = x->r;

        x->splay();
        root = x;
        
        move(0);
    }

    ~SplayTree()
    {
        delete root;
        root = nullptr;
    }

    void kth(int k)
    {
        ++k; // compensate for left dummy;

        Node* x = root;
        for (;;)
        {
            while (x->l && x->l->size >= k)
            {
                x = x->l;
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
        }

        x->splay();
        root = x;
    }

    void move(int k)
    {
        kth(k);
    }

    void next()
    {
        kth(get_k() + 1);
    }

    void prev()
    {
        kth(get_k() - 1);
    }

    void insert(const char* s)
    {
        int k = get_k();

        Node* right_tree = root->r;
        
        Node* x = root->r = new Node{ *s++ };
        x->p = root;

        while (*s)
        {
            x->r = new Node{ *s++ };
            x->r->p = x;
            x = x->r;
        }

        x->r = right_tree;
        if (right_tree)
        {
            right_tree->p = x;
        }

        x->splay();
        root = x;

        kth(k);
    }
    
    void remove(int n)
    {
        int k = get_k();

        gather(k + 1, k + n);
        Node* rmv = root->r->l;
        root->r->l = nullptr;
        delete rmv;

        kth(k);
    }

    void gather(int n)
    {
        int k = get_k();

        gather(k + 1, k + n);
        Node* x = root->r->l;
        x->traverse_print();
        std::cout << '\n';

        kth(k);
    }

private:
    void gather(int l, int r)
    {
        kth(r + 1);
        Node* tmp = root;
        kth(l - 1);
        tmp->splay(root);
    }

    int get_k()
    {
        return root->l ? root->l->size : 0;
    }
};

char BUF[2100000];
char OP[30];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    SplayTree stree;

    int k;
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        std::cin >> OP;
        switch (OP[0])
        {
        case 'M':
            std::cin >> k;
            stree.move(k);
            break;
        case 'I':
            std::cin >> k;
            for (int i = 0; i < k; ++i)
            {
                std::cin.get(BUF[i]);
                if (BUF[i] == '\n')
                {
                    --i;
                }
            }
            BUF[k] = 0;

            stree.insert(BUF);

            break;
        case 'D':
            std::cin >> k;
            stree.remove(k);
            break;
        case 'G':
            std::cin >> k;
            stree.gather(k);
            break;
        case 'P':
            stree.prev();
            break;
        default:
            stree.next();
            break;
        }
    }

    return 0;
}