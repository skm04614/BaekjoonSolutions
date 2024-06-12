#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

int MAP[51][51];
int N;

int sol(int parent)
{
    int result = 0;
    int cnt = 0;
    for (int child = 0; child < N; child++)
    {
        if (MAP[parent][child])
        {
            cnt++;
            result += sol(child);
        }
    }

    return result + (cnt == 0);
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int root = -1;
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        int parent;
        std::cin >> parent;
        if (parent == -1)
        {
            root = i;
        }
        else
        {
            MAP[parent][i] = 1;
        }
    }

    int rmv;
    std::cin >> rmv;
    for (int i = 0; i < N; i++)
    {
        MAP[i][rmv] = 0;
    }

    std::cout << (rmv == root ? 0 : sol(root));

    return 0;
}