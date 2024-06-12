#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[20200];
int COST[20200];
int N;

inline int _abs(int x)
{
    return x < 0 ? -x : x;
}

void init(void)
{
    for (int v = 1; v <= N; v++)
    {
        PARENT[v] = v;
        COST[v] = 0;
    }
}

int find(int v)
{
    if (PARENT[v] == v)
    {
        return v;
    }

    int parent = find(PARENT[v]);

    if (parent != PARENT[v])
    {
        COST[v] += COST[PARENT[v]];
    }

    return PARENT[v] = parent;
}

void _union(int v_src, int v_dest)
{
    COST[v_src] += _abs(v_src - v_dest) % 1000;
    PARENT[v_src] = v_dest;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> N;
        init();

        char c;
        for (;;)
        {
            std::cin >> c;
            if (c == 'O')
            {
                break;
            }

            if (c == 'E')
            {
                int v;
                std::cin >> v;
                find(v);
                std::cout << COST[v] << '\n';
            }
            else
            {
                int v_src, v_dest;
                std::cin >> v_src >> v_dest;
                _union(v_src, v_dest);
            }
        }
    }

    return 0;
}