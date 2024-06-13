#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

enum
{
    INIT = 0,
    SUCCESS = 1,
    FAIL = -1
};

int CNT[100100];
int STATUS[100100];
int DEST[100100];
int N;

void reset()
{
    for (int i = 0; i <= 100000; ++i)
    {
        STATUS[i] = INIT;
        CNT[i] = 0;
    }
}

int dfs(int node)
{
    if (STATUS[node])
    {
        return 0;
    }

    if (CNT[node] == 2)
    {
        return 0;
    }

    ++CNT[node];
    int res = dfs(DEST[node]);
    STATUS[node] = (CNT[node] == 2) ? SUCCESS : FAIL;

    return (CNT[node] == 2) + res;
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
        for (int v = 1; v <= N; ++v)
        {
            std::cin >> DEST[v];
        }

        reset();

        int grouped_cnt = 0;
        for (int v = 1; v <= N; ++v)
        {
            grouped_cnt += dfs(v) / 2;
        }
        std::cout << N - grouped_cnt << '\n';
    }

    return 0;
}
