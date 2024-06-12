#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int PARENT[100100];
int N;

void init(void)
{
    for (register int v = 1; v <= N; v++)
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

    return PARENT[v] = find(PARENT[v]);
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
};
Edge EDGES[500500];
int M;

inline void __swap(Edge& e1, Edge& e2)
{
    Edge tmp = e1;
    e1 = e2;
    e2 = tmp;
}

void __heapify(Edge* arr, int size)
{
    for (register int s = 1; s <= size; s++)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            __swap(arr[p], arr[c]);
            c = p;
        }
    }
}

void heap_sort(Edge* arr, int size)
{
    __heapify(arr, size);

    for (register int s = size; s >= 1; s--)
    {
        int max_s = s;
        __swap(arr[1], arr[max_s--]);

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if (c + 1 <= max_s && arr[c + 1] >= arr[c])
            {
                ++c;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            __swap(arr[p], arr[c]);

            p = c;
            c = p << 1;
        }
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    unsigned long long original = 0;
    for (register int i = 1; i <= M; i++)
    {
        Edge& edge = EDGES[i];
        std::cin >> edge.v1 >> edge.v2 >> edge.w;
        original += edge.w;
    }

    init();
    heap_sort(EDGES, M);

    unsigned long long post = 0;
    for (register int i = 1; i <= M; i++)
    {
        const Edge& edge = EDGES[i];

        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        post += edge.w;
    }

    bool is_valid = true;
    for (register int i = 1; i <= N; i++)
    {
        if (find(i) != 1)
        {
            is_valid = false;
            break;
        }
    }

    if (is_valid)
    {
        std::cout << original - post;
    }
    else
    {
        std::cout << -1;
    }

    return 0;
}