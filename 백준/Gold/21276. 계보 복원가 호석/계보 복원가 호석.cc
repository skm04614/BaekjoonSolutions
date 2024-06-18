#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    Node* child[26];
    int id;

    Node() : child{}, id { 0 }
    {

    }

    ~Node()
    {
        for (int i = 0; i < 26; ++i)
        {
            delete child[i];
            child[i] = nullptr;
        }
    }
};

struct Trie
{
    Node* root;

    Trie() : root{ new Node{} }
    {

    }

    ~Trie()
    {
        delete root;
        root = nullptr;
    }

    void insert(const char* s, int id)
    {
        Node* node = root;
        for (; *s; ++s)
        {
            Node*& child = node->child[*s - 'a'];
            if (child == nullptr)
            {
                child = new Node{};
            }

            node = child;
        }

        node->id = id;
    }

    int search(const char* s)
    {
        const Node* node = root;
        for (; *s; ++s)
        {
            node = node->child[*s - 'a'];
        }
        return node->id;
    }
};

struct Person
{
    char name[7];

    bool operator<=(const Person& other) const
    {
        const char* s1 = name;
        const char* s2 = other.name;
        while (*s1 == *s2)
        {
            ++s1;
            ++s2;
        }
        
        return *s1 <= *s2;
    }

    bool operator>(const Person& other) const
    {
        return !(*this <= other);
    }
};

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void q_sort(T* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = pivot + 1;
    int right = idx1;
    for (;;)
    {
        while (left <= right && arr[pivot] > arr[left])
        {
            ++left;
        }

        while (left <= right && arr[pivot] <= arr[right])
        {
            --right;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            break;
        }

        swap(arr[left], arr[right]);
    }

    q_sort(arr, idx0, right - 1);
    q_sort(arr, right + 1, idx1);
}

struct Edge
{
    int v;
    Edge* next;

    Edge(int v, Edge* next) : v{ v }, next{ next }
    {

    }

    ~Edge()
    {
        delete next;
        next = nullptr;
    }
};

Person ARR[1010];
int IN_DEGREES[1010];
int LEVEL[1010];
Edge* EDGES[1010];
int N;

int Q[1010];
int LP, RP;

int ANCESTORS[1010];
int A;

int CHILD[1010];
int C;

void cleanup()
{
    for (int i = 1; i <= N; ++i)
    {
        delete EDGES[i];
        EDGES[i] = nullptr;
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    Trie trie;

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i].name;
    }
    q_sort(ARR, 1, N);
    for (int i = 1; i <= N; ++i)
    {
        trie.insert(ARR[i].name, i);
    }

    int M;
    std::cin >> M;
    while (M--)
    {
        char buf_1[7] = "";
        char buf_0[7] = "";
        std::cin >> buf_1 >> buf_0;

        int v1 = trie.search(buf_1);
        int v0 = trie.search(buf_0);

        ++IN_DEGREES[v1];
        EDGES[v0] = new Edge{ v1, EDGES[v0] };
    }

    for (int v = 1; v <= N; ++v)
    {
        if (IN_DEGREES[v] == 0)
        {
            ANCESTORS[++A] = v;
            LEVEL[v] = 1;
            Q[++RP] = v;
        }
    }

    while (RP > LP)
    {
        const int c = Q[++LP];
        for (const Edge* e = EDGES[c]; e; e = e->next)
        {
            const int n = e->v;
            if (--IN_DEGREES[n] == 0)
            {
                LEVEL[n] = LEVEL[c] + 1;
                Q[++RP] = n;
            }
        }
    }

    std::cout << A << '\n';
    for (int i = 1; i <= A; ++i)
    {
        std::cout << ARR[ANCESTORS[i]].name << ' ';
    }
    std::cout << '\n';

    for (int v = 1; v <= N; ++v)
    {
        std::cout << ARR[v].name << ' ';

        C = 0;
        for (const Edge* e = EDGES[v]; e; e = e->next)
        {
            if (LEVEL[v] != LEVEL[e->v] - 1)
            {
                continue;
            }

            CHILD[++C] = e->v;
        }

        q_sort(CHILD, 1, C);

        std::cout << C << ' ';
        for (int c = 1; c <= C; ++c)
        {
            std::cout << ARR[CHILD[c]].name << ' ';
        }
        std::cout << '\n';
    }
    
    cleanup();
    return 0;
}
