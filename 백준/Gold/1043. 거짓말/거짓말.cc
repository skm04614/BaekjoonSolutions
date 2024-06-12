#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int min(int x, int y)
{
    return x < y ? x : y;
}

int PARENT[51];
int N;
int LIAR;

int PARTY[51][51];
int PARTY_SIZE[51];
int M;

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
    v1 = find(v1);
    v2 = find(v2);
    
    if (v1 < v2)
    {
        PARENT[v2] = v1;
        if (v2 == LIAR)
        {
            LIAR = v1;
        }
    }
    else
    {
        PARENT[v1] = v2;
        if (v1 == LIAR)
        {
            LIAR = v2;
        }
    }
}

void init()
{
    std::cin >> N >> M;
    for (int v = 1; v <= N; ++v)
    {
        PARENT[v] = v;
    }

    int liar_cnt;
    std::cin >> liar_cnt;
    if (liar_cnt)
    {
        std::cin >> LIAR;
        while (--liar_cnt)
        {
            int liar;
            std::cin >> liar;
            _union(liar, LIAR);
        }
    }

    for (int i = 1; i <= M; ++i)
    {
        std::cin >> PARTY_SIZE[i];
        std::cin >> PARTY[i][1];
        for (int j = 2; j <= PARTY_SIZE[i]; ++j)
        {
            std::cin >> PARTY[i][j];
            _union(PARTY[i][1], PARTY[i][j]);
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    int cnt = M;
    for (int i = 1; i <= M; ++i)
    {
        for (int j = 1; j <= PARTY_SIZE[i]; ++j)
        {
            if (find(PARTY[i][j]) == LIAR)
            {
                --cnt;
                break;
            }
        }
    }
    std::cout << cnt;

    return 0;
}