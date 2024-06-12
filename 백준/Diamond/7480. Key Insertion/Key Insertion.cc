#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_SIZE = 270000;

int PARENT[MAX_SIZE + 10];

int RES[MAX_SIZE + 10];
int R;

void init()
{
    for (int i = 0; i < sizeof(PARENT) / sizeof(PARENT[0]); ++i)
    {
        PARENT[i] = i;
    }
}

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
    v1 = find(v1);
    v2 = find(v2);

    if (v1 == v2)
    {
        return;
    }

    if (v1 > v2)
    {
        PARENT[v2] = v1;
    }
    else
    {
        PARENT[v1] = v2;
    }
}

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
    int N;

    SplayTree(int N) : N{ N }, root{}
    {
        root = new Node{ -0x7FFFFFFF };

        Node* current = root;
        for (int i = 0; i < N; ++i)
        {
            current->r = new Node{ 0 };
            current->r->p = current;
            current = current->r;
        }

        current->r = new Node{ 0x7FFFFFFF };
        current->r->p = current;
        current = current->r;

        current->splay();
        root = current;
    }

    ~SplayTree()
    {
        delete root;
        root = nullptr;
    }

    void kth(int k)
    {
        ++k; // compensate for left dummy node

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

    void set(int k, int val)
    {
        kth(k);

        if (root->val == 0)
        {
            root->val = val;
            return;
        }

        Node* new_node = new Node{ val };
        new_node->l = root->l;
        new_node->p = root;
        root->l = root->l->p = new_node;

        new_node->splay();
        root = new_node;

        for (int rk = k;;)
        {
            rk = find(rk) + 1;
            kth(rk);

            if (root->val == 0)
            {
                break;
            }

            _union(k, rk);
        }

        Node* l = root->l;
        Node* r = root->r;
        root->l = root->r = nullptr;
        delete root;
        root = nullptr;

        if (l && r)
        {
            l->p = nullptr;

            Node* x = l;
            while (x->r)
            {
                x = x->r;
            }
            x->r = r;
            r->p = x;

            r->splay();
            root = r;
        }
        else if (l)
        {
            root = l;
        }
        else if (r)
        {
            root = r;
        }

        if (root)
        {
            root->p = nullptr;
        }
    }

    int copy_values(int* dest)
    {
        int max_n = 0;
        for (int i = N; i >= 1; --i)
        {
            kth(i);
            if (max_n == 0 && root->val)
            {
                max_n = i;
            }

            dest[i] = root->val;
        }

        return max_n;
    }
};

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    SplayTree stree{ MAX_SIZE };

    int N, M;
    std::cin >> N >> M;
    for (int val = 1; val <= N; ++val)
    {
        int k;
        std::cin >> k;
        stree.set(k, val);
    }

    R = stree.copy_values(RES);

    std::cout << R << '\n';
    for (int i = 1; i <= R; ++i)
    {
        std::cout << RES[i] << ' ';
        find(i);
    }

    return 0;
}
