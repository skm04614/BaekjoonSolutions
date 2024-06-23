#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

int max(int x, int y)
{
    return x > y ? x : y;
}

int CHILD_LIST[60][60];
int N_CHILD[60];
int DP[60];
int N;

void _sort(int* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (DP[arr[p]] <= DP[arr[c]])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);

        const int max_s = s - 1;
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && DP[arr[c | 1]] <= DP[arr[c]])
            {
                c |= 1;
            }

            if (DP[arr[p]] <= DP[arr[c]])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

int dfs(int node)
{
    for (int n = 1; n <= N_CHILD[node]; ++n)
    {
        dfs(CHILD_LIST[node][n]);
    }

    _sort(CHILD_LIST[node], N_CHILD[node]);

    DP[node] = 0;
    for (int n = 1; n <= N_CHILD[node]; ++n)
    {
        DP[node] = max(DP[node], DP[CHILD_LIST[node][n]] + n);
    }

    return DP[node];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> N;
    int p;
    std::cin >> p;
    for (int c = 1; c < N; ++c)
    {
        std::cin >> p;
        CHILD_LIST[p][++N_CHILD[p]] = c;
    }

    std::cout << dfs(0);

    return 0;
}
