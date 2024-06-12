#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Adj
{
    int v;
    Adj* next;

    Adj(int v, Adj* next) : v{v}, next{next}
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

void cleanup()
{
    for (int a = 1; a <= N; ++a)
    {
        delete ADJ[a];
        ADJ[a] = nullptr;
    }
}

bool VISITED[1010];
int B[1010];
int M, K;

void reset()
{
    for (int b = 1; b <= M; ++b)
    {
        VISITED[b] = false;
    }
}

int dfs(const int a)
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
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M >> K;
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
        reset();

        if (dfs(a))
        {
            ++res;
        }

        if (res == M)
        {
            break;
        }
    }

    for (int a = 1; a <= N && K; ++a)
    {
        reset();

        if (dfs(a))
        {
            ++res;
            --K;
        }

        if (res == M)
        {
            break;
        }
    }

    std::cout << res;

    cleanup();
    return 0;
}
