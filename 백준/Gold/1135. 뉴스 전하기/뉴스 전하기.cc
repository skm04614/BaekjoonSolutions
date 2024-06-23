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

int CHILD_LIST[51][51];
int N_CHILD[51];
int DP[51];
int N;

void q_sort(int* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = idx0 + 1;
    int right = idx1;

    for (;;)
    {
        while (left <= right && DP[arr[left]] > DP[arr[pivot]])
        {
            ++left;
        }

        while (left <= right && DP[arr[right]] <= DP[arr[pivot]])
        {
            --right;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            break;
        }

        swap(arr[left], arr[right]);
    }

    q_sort(arr, idx0, right - 1);
    q_sort(arr, right + 1, idx1);
}

int dfs(int node)
{
    for (int n = 1; n <= N_CHILD[node]; ++n)
    {
        dfs(CHILD_LIST[node][n]);
    }

    q_sort(CHILD_LIST[node], 1, N_CHILD[node]);

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
