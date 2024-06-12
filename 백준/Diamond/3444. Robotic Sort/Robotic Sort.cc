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
    int val;
    int size;
    bool lazy;
    Node* l;
    Node* r;
    Node* p;

    Node(int val) : val{ val }, size{ 1 }, lazy{ false }, l{}, r{}, p{}
    {

    }

    ~Node()
    {
        if (l)
        {
            delete l;
        }

        if (r)
        {
            delete r;
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

    void propagate()
    {
        if (lazy)
        {
            swap(l, r);

            if (l)
            {
                l->lazy ^= true;
            }

            if (r)
            {
                r->lazy ^= true;
            }

            lazy = false;
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

    bool operator<=(const Node& other) const
    {
        return val <= other.val;
    }

    void traverse_print() const
    {
        if (l)
        {
            l->traverse_print();
        }

        std::cout << val << '\n';

        if (r)
        {
            r->traverse_print();
        }
    }
};

struct SplayTree
{
    Node* root;
    Node* arr[100100];
    int N;

    SplayTree(int* arr, int N) : root{}, arr{}, N{ N }
    {
        root = new Node{ 0 };

        Node* current = root;
        for (int i = 1; i <= N; i++)
        {
            current->r = new Node{ arr[i] };
            current->r->p = current;
            current = current->r;
            this->arr[i] = current;
        }
        m_sort_arr();

        current->r = new Node{ 0x7FFFFFFF };
        current->r->p = current;
        current = current->r;

        current->splay();
        root = current;
    }

    void m_sort_arr()
    {
        Node** tmp = new Node * [100100]{};
        _m_sort_arr(arr, tmp, 1, N);
        delete[] tmp;
    }

    void _m_sort_arr(Node** arr, Node** tmp, int idx0, int idx1)
    {
        if (idx0 == idx1)
        {
            return;
        }

        int mid = (idx0 + idx1) >> 1;
        _m_sort_arr(arr, tmp, idx0, mid);
        _m_sort_arr(arr, tmp, mid + 1, idx1);

        int left = idx0;
        int right = mid + 1;
        int idx = 0;
        for (;;)
        {
            if (left > mid || right > idx1)
            {
                break;
            }

            if (*arr[left] <= *arr[right])
            {
                tmp[idx++] = arr[left++];
            }
            else
            {
                tmp[idx++] = arr[right++];
            }
        }

        while (left <= mid)
        {
            tmp[idx++] = arr[left++];
        }

        while (right <= idx1)
        {
            tmp[idx++] = arr[right++];
        }

        for (int i = 0; i < idx; i++)
        {
            arr[idx0 + i] = tmp[i];
        }
    }

    void kth(int k)
    {
        ++k; // account for left dummy;

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

    int execute(int k)
    {
        Node* tgt = arr[k];
        tgt->splay();
        root = tgt;

        int k1 = root->l->size;

        tgt = gather(k, k1);
        tgt->lazy = true;

        return k1;
    }
};


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int* arr = new int[100100]{};

    int N;
    for (;;)
    {
        std::cin >> N;
        if (N == 0)
        {
            break;
        }

        for (int i = 1; i <= N; i++)
        {
            std::cin >> arr[i];
        }
        SplayTree stree{ arr, N };
        for (int i = 1; i <= N; i++)
        {
            std::cout << stree.execute(i) << ' ';
        }
        std::cout << '\n';
    }

    delete[] arr;

    return 0;
}