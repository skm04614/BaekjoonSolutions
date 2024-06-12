#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int PFX_START = (1 << 0);
constexpr int SFX_END = (1 << 1);

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

char BUF[2020];
int STATUS[2020];
int N;

char PREFIX[2020];
int PM_P[2020];
int P;

char SUFFIX[2020];
int PM_S[2020];
int S;

void fill_pm(const char* k, int& size, int* pm)
{
    size = _slen(k);

    pm[0] = 0;
    int len = 0;
    for (int i = 1; i < size; ++i)
    {
        while (len && k[len] != k[i])
        {
            len = pm[len - 1];
        }

        if (k[len] == k[i])
        {
            ++len;
        }

        pm[i] = len;
    }
}

void record_status()
{
    N = _slen(BUF);

    int len = 0;
    for (int i = 0; i < N; ++i)
    {
        while (len && PREFIX[len] != BUF[i])
        {
            len = PM_P[len - 1];
        }

        if (PREFIX[len] == BUF[i])
        {
            ++len;
        }

        if (len == P)
        {
            STATUS[i - len + 1] |= PFX_START;
            len = PM_P[len - 1];
        }
    }

    len = 0;
    for (int i = 0; i < N; ++i)
    {
        while (len && SUFFIX[len] != BUF[i])
        {
            len = PM_S[len - 1];
        }

        if (SUFFIX[len] == BUF[i])
        {
            ++len;
        }

        if (len == S)
        {
            STATUS[i] |= SFX_END;
            len = PM_S[len - 1];
        }
    }
}

struct Node
{
    Node* child[26];
    bool end;

    Node() : child{}, end{ false }
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

    int insert(const char* buf, int idx0, int idx1)
    {
        int res = 0;

        Node* current = root;
        for (int i = idx0; i <= idx1; ++i)
        {
            Node*& child = current->child[buf[i] - 'a'];
            if (child == nullptr)
            {
                child = new Node{};
            }

            current = child;

            if ((STATUS[i] & SFX_END) && i >= idx0 + P - 1 && idx0 <= i - S + 1)
            {
                res += !current->end;
                current->end = true;
            }
        }

        return res;
    }
};

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF >> PREFIX >> SUFFIX;

    fill_pm(PREFIX, P, PM_P);
    fill_pm(SUFFIX, S, PM_S);
    
    record_status();

    Trie trie;

    int res = 0;
    for (int i = 0; i < N; ++i)
    {
        if (~STATUS[i] & PFX_START)
        {
            continue;
        }

        res += trie.insert(BUF, i, N - 1);
    }
    std::cout << res;

    return 0;
}
