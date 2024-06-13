#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

bool OCCUPIED[100'100];
int PARENT[100'100];

void init()
{
    for (int i = 0; i < sizeof(PARENT) / sizeof(PARENT[0]); ++i)
    {
        PARENT[i] = i;
        OCCUPIED[i] = false;
    }
}

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

    init();

    int G, P;
    std::cin >> G >> P;

    int cnt = 0;
    for (int i = 0; i < P; ++i)
    {
        int gi;
        std::cin >> gi;
        
        while (gi && OCCUPIED[gi])
        {
            _union(gi, gi - 1);
            gi = find(gi);
        }

        if (gi == 0)
        {
            break;
        }

        ++cnt;
        OCCUPIED[gi] = true;
    }

    std::cout << cnt;

    return 0;
}