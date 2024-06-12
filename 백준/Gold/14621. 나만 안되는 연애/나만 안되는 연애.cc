#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

// N 1000 M 10000
int IS_MALE[1010];
int PARENT[1010];
int N;

void init(void)
{
    for (int v = 1; v <= N; v++)
    {
        PARENT[v] = v;
    }
}

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
    int w;

    bool operator>=(const Edge& other) const
    {
        return w >= other.w;
    }

    bool operator<=(const Edge& other) const
    {
        return w <= other.w;
    }
};

Edge EDGES[10010];
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
    for (int v = 1; v <= N; v++)
    {
        char c;
        std::cin >> c;
        IS_MALE[v] = (c == 'M');
    }
    init();
    
    for (int m = 1; m <= M; m++)
    {
        int v1, v2, w;
        std::cin >> v1 >> v2 >> w;

        if (IS_MALE[v1] != IS_MALE[v2])
        {
            EDGES[++E] = { v1, v2, w };
        }
    }
    q_sort(EDGES, 1, E);

    int sol = 0;
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

    bool is_valid = true;
    for (int i = 2; i <= N; i++)
    {
        if (find(i) != find(1))
        {
            is_valid = false;
            break;
        }
    }

    std::cout << (is_valid ? sol : -1);

    return 0;
}