#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    int val;
    int size;

    Node* l;
    Node* r;
    Node* p;

    Node(int val) : val{ val }, size{ 1 }, l{}, r{}, p{}
    {

    }

    ~Node()
    {
        delete l;
        l = nullptr;

        delete r;
        r = nullptr;
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

        std::cout << val << ' ';

        if (r)
        {
            r->traverse_print();
        }
    }
};

struct SplayTree
{
    Node* root;
    Node** arr;
    int N;

    SplayTree(int N) : N{ N }, arr{ nullptr }
    {
        arr = new Node * [N + 2];

        Node* current = arr[0] = new Node{ 0 };
        root = current;
        for (int n = 1; n <= N + 1; n++)
        {
            current->r = arr[n] = new Node{ n };
            current->r->p = current;
            current = current->r;
        }

        current->splay();
        root = current;
    }

    ~SplayTree()
    {
        delete root;
        delete[] arr;
        arr = nullptr;
    }

    void kth(int k)
    {
        ++k; // for left dummy

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

    void gather(int k0, int k1)
    {
        kth(k1 + 1);
        Node* tmp = root;
        kth(k0 - 1);
        tmp->splay(root);
    }

    void last_traverse()
    {
        gather(1, N);
        root->r->l->traverse_print();
    }

    int slide(int a, int b)
    {
        Node* node_a = arr[a];
        Node* node_b = arr[b];

        node_a->splay();
        root = node_a;
        
        int k0 = root->l->size;
        gather(k0, k0);

        {
            root->r->l->p = nullptr;
            root->r->l = nullptr;
            Node* tmp = root->r->r ? root->r->r : root->r;
            tmp->splay();
            root = tmp;
        }

        node_b->splay();
        root = node_b;
        int k_b = root->l->size;

        Node* tmp = root->r;
        root->r = tmp->p = node_a;
        node_a->p = root;
        node_a->r = tmp;

        tmp->splay();
        root = tmp;

        return (k_b + 1) - k0;
    }
};

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, M;
    std::cin >> N >> M;

    SplayTree stree{ N };

    while (M--)
    {
        int a, b;
        std::cin >> a >> b;

        std::cout << stree.slide(a, b) << '\n';
    }
    stree.last_traverse();

    return 0;
}