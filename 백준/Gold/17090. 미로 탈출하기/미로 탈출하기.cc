#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[300300];


int N, M;

void init(void)
{
    for (int v = 0; v <= N * M; v++)
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

    return PARENT[v] = find(PARENT[v]);
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

int convert_to_vertex(int y, int x)
{
    return 1 + (y * M) + x;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;

    init();

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            char c;
            std::cin >> c;
            
            int y = i;
            int x = j;
            if (c == 'U')
            {
                y--;
            }
            else if (c == 'D')
            {
                y++;
            }
            else if (c == 'L')
            {
                x--;
            }
            else
            {
                x++;
            }

            if (y < 0 || y >= N || x < 0 || x >= M)
            {
                y = 0;
                x = -1;
            }

            _union(convert_to_vertex(i, j), convert_to_vertex(y, x));
        }
    }

    int sol = 0;
    for (int v = 1; v <= N * M; v++)
    {
        if (find(v) == 0)
        {
            sol++;
        }
    }
    std::cout << sol;

    return 0;
}