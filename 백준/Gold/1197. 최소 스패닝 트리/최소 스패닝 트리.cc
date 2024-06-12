#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

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

inline void swap(Edge& e1, Edge& e2)
{
    Edge tmp = e1;
    e1 = e2;
    e2 = tmp;
}

void _qsort(Edge* arr, int idx0, int idx1)
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

    _qsort(arr, idx0, right - 1);
    _qsort(arr, right + 1, idx1);
}

int PARENT[10100];
int V;

Edge ARR[100100];
int E;

void init()
{
    for (int v = 1; v <= V; v++)
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

    std::cin >> V >> E;
    for (int i = 0; i < E; i++)
    {
        std::cin >> ARR[i].v1 >> ARR[i].v2 >> ARR[i].w;
    }
    _qsort(ARR, 0, E - 1);

    int sol = 0;
    init();
    for (int i = 0; i < E; i++)
    {
        const Edge& edge = ARR[i];
        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        sol += edge.w;
        _union(edge.v1, edge.v2);
    }
    std::cout << sol;

    return 0;
}