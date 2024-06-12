#include <iostream>

using ull = unsigned long long;

inline ull min(const ull& x, const ull& y)
{
    return x < y ? x : y;
}

inline ull max(const ull& x, const ull& y)
{
    return x > y ? x : y;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Node
{
    ull val;
    ull _max;
    ull _min;
    ull _sum;
    int size;
    bool flip;

    Node* l;
    Node* r;
    Node* p;

    Node(ull val)
        : val{ val },
        _max{ val },
        _min{ val },
        _sum{ val },
        size{ 1 },
        flip{ false },
        l{},
        r{},
        p{}
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
        _min = _max = _sum = val;

        if (l)
        {
            _min = min(_min, l->_min);
            _max = max(_max, l->_max);
            _sum += l->_sum;
            size += l->size;
        }

        if (r)
        {
            _min = min(_min, r->_min);
            _max = max(_max, r->_max);
            _sum += r->_sum;
            size += r->size;
        }
    }

    void propagate()
    {
        if (flip)
        {
            swap(l, r);

            if (l)
            {
                l->flip ^= true;
            }

            if (r)
            {
                r->flip ^= true;
            }

            flip = false;
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
                break;
            }

            if (g)
            {
                ((p == g->l) == (x == p->l) ? p : x)->rotate();
            }
            x->rotate();
        }
    }

    void traverse_print()
    {
        propagate();

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

    SplayTree(int N) : root{}, N{ N }, arr{}
    {
        arr = new Node * [N + 10]{};
        root = new Node{ 0 };

        Node* current = root;
        for (ull n = 1; n <= N; n++)
        {
            current->r = new Node{ n };
            current->r->p = current;
            current = current->r;
            arr[n] = current;
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

        delete[] arr;
        arr = nullptr;
    }

    void kth(int k)
    {
        ++k; // for left dummy

        Node* current = root;
        current->propagate();
        for (;;)
        {
            while (current->l && current->l->size >= k)
            {
                current = current->l;
                current->propagate();
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
            current->propagate();
        }

        current->splay();
        root = current;
    }

    Node* gather(int k0, int k1)
    {
        kth(k1 + 1);
        Node* tmp = root;
        kth(k0 - 1);
        tmp->splay(root);

        return root->r->l;
    }

    void action_1(int l, int r)
    {
        Node* x = gather(l, r);

        std::cout << x->_min << ' ' << x->_max << ' ' << x->_sum << '\n';

        x->flip ^= true;
    }

    void action_2(int l, int r, int d)
    {
        Node* x = gather(l, r);

        std::cout << x->_min << ' ' << x->_max << ' ' << x->_sum << '\n';

        int D = (r - l + 1);

        d %= D;
        if (d < 0)
        {
            d += D;
        }

        if (d == 0)
        {
            return;
        }

        x->flip ^= true;

        Node* y = gather(l, l + d - 1);
        y->flip ^= true;

        Node* z = gather(l + d, r);
        z->flip ^= true;
    }

    void action_3(int k)
    {
        kth(k);
        std::cout << root->val << '\n';
    }

    void action_4(int n)
    {
        Node* x = arr[n];
        x->splay();
        root = x;

        std::cout << root->l->size << '\n';
    }

    void final_action()
    {
        Node* x = gather(1, N);
        x->traverse_print();
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
        int opt;
        std::cin >> opt;
        if (opt == 1)
        {
            int l, r;
            std::cin >> l >> r;
            stree.action_1(l, r);
        }
        else if (opt == 2)
        {
            int l, r, d;
            std::cin >> l >> r >> d;
            stree.action_2(l, r, d);
        }
        else if (opt == 3)
        {
            int k;
            std::cin >> k;
            stree.action_3(k);
        }
        else
        {
            int n;
            std::cin >> n;
            stree.action_4(n);
        }
    }
    stree.final_action();

    return 0;
}
