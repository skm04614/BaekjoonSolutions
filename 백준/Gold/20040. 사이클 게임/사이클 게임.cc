#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[500500];
int N;
int M;

void init(void)
{
    for (int i = 1; i <= N; i++)
    {
        PARENT[i] = i;
    }
}

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return (v = find(PARENT[v]));
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
    
    std::cin >> N >> M;
    init();

    int sol = 0;
    for (int i = 1; i <= M; i++)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        if (find(v1) == find(v2))
        {
            sol = i;
            break;
        }

        _union(v1, v2);
    }
    std::cout << sol;

    return 0;
}