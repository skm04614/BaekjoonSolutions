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
    
    SplayTree(const char* str)
    {
        root = new Node{ '-' };

        Node* current = root;
        while (*str)
        {
            current->r = new Node{ *str++ };
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
        k0 += 2; // convert to 1-base + left dummy
        k1 += 2; // convert to 1-base + left dummy

        kth(k1 + 1);
        Node* tmp = root;
        kth(k0 - 1);
        tmp->splay(root);
    }

    char get_char(int k)
    {
        k += 2; //convert to 1-base + left dummy
        kth(k);
        return root->chr;
    }

    void move_front(int k0, int k1)
    {
        gather(k0, k1);

        Node* subtree = root->r->l;
        root->r->l = nullptr;

        Node* new_root = root->r;
        new_root->splay();
        root = new_root;

        kth(2);

        Node* left_dummy = root->l;
        root->l = subtree;
        subtree->p = root;

        while (subtree->l)
        {
            subtree = subtree->l;
        }
        subtree->l = left_dummy;
        left_dummy->p = subtree;

        left_dummy->splay();
        root = left_dummy;
    }

    void move_back(int k0, int k1)
    {
        gather(k0, k1);

        Node* subtree = root->r->l;
        root->r->l = nullptr;

        Node* new_root = root->r;
        new_root->splay();
        root = new_root;

        kth(root->size - 1);

        Node* right_dummy = root->r;
        root->r = subtree;
        subtree->p = root;

        while (subtree->r)
        {
            subtree = subtree->r;
        }
        subtree->r = right_dummy;
        right_dummy->p = subtree;

        right_dummy->splay();
        root = right_dummy;
    }
};


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char* buf = new char[100100];
    std::cin >> buf;
    SplayTree stree{ buf };
    delete[] buf;

    int N;
    std::cin >> N;
    while (N--)
    {
        int opt;
        std::cin >> opt;
        if (opt == 3)
        {
            int k;
            std::cin >> k;
            std::cout << stree.get_char(k) << '\n';
        }
        else
        {
            int k0, k1;
            std::cin >> k0 >> k1;

            if (opt == 1)
            {
                stree.move_front(k0, k1);
            }
            else
            {
                stree.move_back(k0, k1);
            }
        }
    }

    return 0;
}