#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

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
int VISITED[1010];
int N;

int B[1010];
int M;

void reset()
{
    for (int a = 1; a <= N; ++a)
    {
        VISITED[a] = 0;
    }
}

void cleanup()
{
    for (int a = 1; a <= N; ++a)
    {
        delete ADJ[a];
        ADJ[a] = nullptr;
    }
}

bool dfs(const int a)
{
    if (VISITED[a] >= 2)
    {
        return false;
    }

    ++VISITED[a];

    for (const Adj* adj = ADJ[a]; adj; adj = adj->next)
    {
        const int b = adj->v;
        if (!B[b] || VISITED[B[b]] < 2 && dfs(B[b]))
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
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int a = 1; a <= N; ++a)
    {
        int cnt;
        std::cin >> cnt;

        while (cnt--)
        {
            int b;
            std::cin >> b;
            ADJ[a] = new Adj{ b, ADJ[a] };
        }
    }

    int res = 0;
    for (int a = 1; a <= N; ++a)
    {
        for (int i = 0; i < 2; ++i)
        {
            reset();
            if (dfs(a))
            {
                ++res;
            }
        }

        if (res == M)
        {
            break;
        }
    }
    std::cout << res;

    return 0;
}
