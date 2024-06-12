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

int PARENT[100100];
int N;

void init()
{
    for (int v = 1; v <= N; v++)
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

Edge ARR[1000100];
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

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        std::cin >> ARR[i].v1 >> ARR[i].v2 >> ARR[i].w;
    }
    q_sort(ARR, 0, M - 1);

    int sol = 0;
    int max_w = 0;
    init();
    for (int i = 0; i < M; i++)
    {
        const Edge& edge = ARR[i];

        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        sol += edge.w;
        max_w = max_w > edge.w ? max_w : edge.w;
    }
    std::cout << sol - max_w;


    return 0;
}