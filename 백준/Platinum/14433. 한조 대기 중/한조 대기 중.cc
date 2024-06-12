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

Adj* ADJ[2][310];
int N;

bool VISITED[2][310];
int B[2][310];
int M;

void init(int idx)
{
    for (int b = 1; b <= M; ++b)
    {
        VISITED[idx][b] = false;
    }
}

bool dfs(int a, int idx)
{
    for (const Adj* adj = ADJ[idx][a]; adj; adj = adj->next)
    {
        const int b = adj->v;
        if (VISITED[idx][b])
        {
            continue;
        }

        VISITED[idx][b] = true;

        if (!B[idx][b] || dfs(B[idx][b], idx))
        {
            B[idx][b] = a;
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

    int k[2] = {};
    std::cin >> N >> M >> k[0] >> k[1];
    for (int i = 0; i < 2; ++i)
    {
        while (k[i]--)
        {
            int a, b;
            std::cin >> a >> b;
            ADJ[i][a] = new Adj{ b, ADJ[i][a] };
        }
    }

    int cnt[2] = {};
    for (int idx = 0; idx < 2; ++idx)
    {
        for (int a = 1; a <= N; ++a)
        {
            init(idx);
            cnt[idx] += dfs(a, idx);
        }
    }

    std::cout << ((cnt[0] >= cnt[1]) ? "그만 알아보자" : "네 다음 힐딱이");

    return 0;
}
