#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <iomanip>

struct Coords
{
    double x;
    double y;

    double dist_to(const Coords& other) const
    {
        double dx = x - other.x;
        double dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};

Coords COORDS[1010];
int PARENT[1010];
int N;

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

struct Edge
{
    int v1;
    int v2;
    double w;

    bool operator>=(const Edge& other)
    {
        return w >= other.w;
    }

    bool operator<=(const Edge& other)
    {
        return w <= other.w;
    }
};

Edge EDGES[1001000];
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

    int M;
    std::cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> COORDS[i].y >> COORDS[i].x;
        PARENT[i] = i;
    }

    for (int i = 1; i <= M; i++)
    {
        int v1;
        int v2;
        std::cin >> v1 >> v2;

        if (find(v1) == find(v2))
        {
            continue;
        }

        _union(v1, v2);
    }

    for (int i = 1; i <= N; i++)
    {
        for (int j = i + 1; j <= N; j++)
        {
            EDGES[++E] = { i, j, COORDS[i].dist_to(COORDS[j]) };
        }
    }
    q_sort(EDGES, 1, E);

    double sol = 0;
    for (int i = 1; i <= E; i++)
    {
        const Edge& edge = EDGES[i];

        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        sol += edge.w;
    }
    std::cout << std::fixed << std::setprecision(2) << sol;

    return 0;
}