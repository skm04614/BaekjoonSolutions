#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char MAP[1010][1010];
int N, M;

int PARENT[1001000];

int find(int v)
{
    if (PARENT[v] == v)
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

    std::cin >> N >> M;
    for (int i = 0; i < N; i++)
    {
        std::cin >> MAP[i];
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int k = i * M + j;
            PARENT[k] = k;
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            int k[2] = { i * M + j };
            if (MAP[i][j] == 'R')
            {
                k[1] = k[0] + 1;
            }
            else if (MAP[i][j] == 'L')
            {
                k[1] = k[0] - 1;
            }
            else if (MAP[i][j] == 'D')
            {
                k[1] = k[0] + M;
            }
            else
            {
                k[1] = k[0] - M;
            }
            _union(k[0], k[1]);
        }
    }

    int sol = 0;
    for (int k = 0; k < N * M; k++)
    {
        sol += (find(k) == k);
    }
    std::cout << sol;


    return 0;
}