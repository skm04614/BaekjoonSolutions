#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    Node* child[26];
    int id;

    Node() : child{}, id{ 0 }
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

    void insert(const char* name, int id)
    {
        Node* node = root;
        while (*name)
        {
            Node*& child = node->child[*name - 'A'];
            if (child == nullptr)
            {
                child = new Node{};
            }

            node = child;
            ++name;
        }

        node->id = id;
    }

    int get_id(const char* name)
    {
        const Node* node = root;
        while (*name)
        {
            const Node* child = node->child[*name - 'A'];
            if (child == nullptr)
            {
                return 0;
            }

            node = child;
            ++name;
        }

        return node->id;
    }
};

struct Adj
{
    int v;
    Adj* next;

    Adj(int v, Adj* next) : v{ v }, next{ next }
    {

    }

    ~Adj()
    {
        delete next;
        next = nullptr;
    }
};

Adj* ADJ[1010];
int N;

bool VISITED[1010];
int B[1010];
int M;

void cleanup()
{
    for (int i = 0; i < sizeof(ADJ) / sizeof(ADJ[0]); ++i)
    {
        delete ADJ[i];
        ADJ[i] = nullptr;
    }
}

void init()
{
    for (int b = 1; b <= M; ++b)
    {
        VISITED[b] = false;
    }
}

bool dfs(int a)
{
    for (const Adj* adj = ADJ[a]; adj; adj = adj->next)
    {
        const int b = adj->v;
        if (VISITED[b])
        {
            continue;
        }

        VISITED[b] = true;
        if (!B[b] || dfs(B[b]))
        {
            B[b] = a;
            return true;
        }
    }

    return false;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N >> M;

    Trie trie;
    char buf[110] = "";
    for (int b = 1; b <= M; ++b)
    {
        std::cin >> buf;
        trie.insert(buf, b);
    }

    for (int a = 1; a <= N; ++a)
    {
        int cnt;
        std::cin >> cnt;
        while (cnt--)
        {
            std::cin >> buf;
            int b = trie.get_id(buf);
            ADJ[a] = new Adj{ b, ADJ[a] };
        }
    }

    int cnt = 0;
    for (int a = 1; a <= N; ++a)
    {
        init();
        cnt += dfs(a);
        if (cnt == M)
        {
            break;
        }
    }

    if (cnt == N)
    {
        std::cout << "YES";
    }
    else
    {
        std::cout << "NO\n" << cnt;
    }

    cleanup();
    return 0;
}
