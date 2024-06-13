#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

struct Edge
{
    int v1;
    int v2;
    int w;

    bool operator<=(const Edge& other) const
    {
        return w <= other.w;
    }

    bool operator>=(const Edge& other) const
    {
        return w >= other.w;
    }
};

Edge EDGES[30010];
int M;

inline void swap(Edge& e1, Edge& e2)
{
    Edge tmp = e1;
    e1 = e2;
    e2 = tmp;
}

void q_sort(Edge* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = pivot + 1;
    int right = idx1;
    for (;;)
    {
        while (left <= right && arr[right] >= arr[pivot])
        {
            right--;
        }

        while (left <= right && arr[left] <= arr[pivot])
        {
            left++;
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

int PARENT[10010];
int N;
int T;

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

    std::cin >> N >> M >> T;
    for (int v = 1; v <= N; v++)
    {
        PARENT[v] = v;
    }

    for (int i = 1; i <= M; i++)
    {
        Edge& edge = EDGES[i];
        std::cin >> edge.v1 >> edge.v2 >> edge.w;
    }

    q_sort(EDGES, 1, M);

    ull cost = 0;
    ull t = 0;
    for (int i = 1; i <= M; i++)
    {
        const Edge& edge = EDGES[i];
        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        cost += edge.w + t;
        t += T;
    }
    std::cout << cost;

    return 0;
}