#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[1000010];
int N;
int M;

void init(void)
{
    for (int v = 0; v < N; v++)
    {
        PARENT[v] = v;
    }
}

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return (PARENT[v] = find(PARENT[v]));
}

void _union(int v1, int v2)
{
    v1 = find(v1);
    v2 = find(v2);

    if (v1 < v2)
    {
        PARENT[v2] = v1;
    }
    else
    {
        PARENT[v1] = v2;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    for (int t = 1; t <= T; t++)
    {
        std::cout << "Scenario " << t << ":\n";
        std::cin >> N;

        init();

        std::cin >> M;
        for (int j = 0; j < M; j++)
        {
            int v1, v2;
            std::cin >> v1 >> v2;
            _union(v1, v2);
        }

        std::cin >> M;
        for (int j = 0; j < M; j++)
        {
            int v1, v2;
            std::cin >> v1 >> v2;
            std::cout << (find(v1) == find(v2) ? 1 : 0) << '\n';
        }

        std::cout << '\n';
    }

    return 0;
}