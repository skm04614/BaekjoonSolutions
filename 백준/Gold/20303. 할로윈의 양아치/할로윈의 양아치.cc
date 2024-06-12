#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int PARENT[30030];
int CANDIES[30030];
int SIZE[30030];
int N;
int K;

int DP[3030];

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

    if (v1 == v2)
    {
        return;
    }
    
    if (v1 < v2)
    {
        PARENT[v2] = v1;
        CANDIES[v1] += CANDIES[v2];
        SIZE[v1] += SIZE[v2];

        CANDIES[v2] = SIZE[v2] = 0;
    }
    else
    {
        PARENT[v1] = v2;
        CANDIES[v2] += CANDIES[v1];
        SIZE[v2] += SIZE[v1];

        CANDIES[v1] = SIZE[v1] = 0;
    }
}

void init()
{
    int M;
    std::cin >> N >> M >> K;

    for (int v = 1; v <= N; ++v)
    {
        PARENT[v] = v;
        std::cin >> CANDIES[v];
        SIZE[v] = 1;
    }

    while (M--)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        _union(v1, v2);
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    int sol = DP[0] = 0;
    for (int v = 1; v <= N; ++v)
    {
        int s = SIZE[v];
        int c = CANDIES[v];
        if (s == 0)
        {
            continue;
        }

        for (int k = K - 1; k >= s; --k)
        {
            DP[k] = max(DP[k], DP[k - s] + c);
            sol = max(sol, DP[k]);
        }
    }

    std::cout << sol;

    return 0;
}