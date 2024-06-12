#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>

struct Coords
{
    double x;
    double y;

    double dist_sq(const Coords& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};

Coords COORDS[110];
int PARENT[110];
int N;

void init(void)
{
    for (int v = 0; v < N; v++)
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

struct Edge
{
    int v1;
    int v2;
    double w;

    bool operator>=(const Edge& other) const
    {
        return w >= other.w;
    }

    bool operator<=(const Edge& other) const
    {
        return w <= other.w;
    }
};

Edge EDGES[10100];
int E;

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

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        std::cin >> COORDS[i].x >> COORDS[i].y;
    }
    init();

    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            EDGES[E].v1 = i;
            EDGES[E].v2 = j;
            EDGES[E].w = COORDS[i].dist_sq(COORDS[j]);
            E++;
        }
    }
    q_sort(EDGES, 0, E - 1);

    double cost = 0;
    for (int i = 0; i < E; i++)
    {
        const Edge& edge = EDGES[i];
        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        cost += edge.w;
    }
    std::cout << cost;

    return 0;
}