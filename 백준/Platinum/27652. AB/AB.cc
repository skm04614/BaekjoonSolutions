#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Node
{
    Node* child[26];
    bool end;
    int cnt;

    Node() : child{}, end{ false }, cnt{ 0 }
    {
    
    }

    ~Node()
    {
        for (int i = 0; i < 26; i++)
        {
            if (child[i])
            {
                delete child[i];
            }
        }
    }
};

struct Trie
{
    Node root;

    Trie() : root{}
    {

    }

    void insert(const char* word)
    {
        insert(&root, word);
    }

    void remove(const char* word)
    {
        remove(&root, word);
    }

    void get_cnt(const char* word, int* record) const
    {
        get_cnt(&root, word, 1, record);
    }

private:
    void insert(Node* node, const char* word)
    {
        node->cnt++;

        if (*word == 0)
        {
            node->end = true;
            return;
        }

        Node*& child = node->child[*word - 'a'];
        if (child == nullptr)
        {
            child = new Node{};
        }

        insert(child, word + 1);
    }

    void remove(Node* node, const char* word)
    {
        node->cnt--;

        if (*word == 0)
        {
            node->end = false;
            return;
        }

        Node*& child = node->child[*word - 'a'];
        remove(child, word + 1);

        if (child->cnt == 0)
        {
            delete child;
            child = nullptr;
        }
    }

    void get_cnt(const Node* node, const char* word, int depth, int* record) const
    {
        if (*word == 0)
        {
            return;
        }

        if (node)
        {
            Node* const& child = node->child[*word - 'a'];
            record[depth] = child ? child->cnt : 0;
            get_cnt(child, word + 1, depth + 1, record);
        }
        else
        {
            record[depth] = 0;
            get_cnt(nullptr, word + 1, depth + 1, record);
        }
    }
};

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { len++; }
    return len;
}

void _s_rev_cpy(char* dest, const char* src)
{
    int len = _slen(src);
    for (int i = 0; i < len; i++)
    {
        dest[i] = src[len - 1 - i];
    }
    dest[len] = 0;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    Trie trie_a;
    Trie trie_b;

    char op[10] = {};
    char c = {};
    char word[1100] = {};
    char word2[1100] = {};

    int cnt_a[1100] = {};
    int cnt_b[1100] = {};

    int N;
    std::cin >> N;
    while (N--)
    {
        std::cin >> op;
        if (op[0] == 'a')
        {
            std::cin >> c >> word;
            if (c == 'A')
            {
                trie_a.insert(word);
            }
            else
            {
                _s_rev_cpy(word2, word);
                trie_b.insert(word2);
            }
        }
        else if (op[0] == 'd')
        {
            std::cin >> c >> word;
            if (c == 'A')
            {
                trie_a.remove(word);
            }
            else
            {
                _s_rev_cpy(word2, word);
                trie_b.remove(word2);
            }
        }
        else
        {
            std::cin >> word;
            _s_rev_cpy(word2, word);

            trie_a.get_cnt(word, cnt_a);
            trie_b.get_cnt(word2, cnt_b);

            int sol = 0;
            int limit = _slen(word);
            for (int size = 1; size < limit; size++)
            {
                sol += cnt_a[size] * cnt_b[limit - size];
            }
            std::cout << sol << '\n';
        }
    }

    return 0;
}