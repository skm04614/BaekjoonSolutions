#include <iostream>

using ull = unsigned long long;

int PARENT[200200];
int N;

ull OLD;
ull NEW;

void init(void)
{
    OLD = 0;
    NEW = 0;

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
    ull w;

    bool operator>=(const Edge& other) const
    {
        return w >= other.w;
    }
};

Edge EDGES[200200];
int M;

void swap(Edge& e1, Edge& e2)
{
    Edge tmp = e1;
    e1 = e2;
    e2 = tmp;
}

void sort(Edge* arr, int size)
{
    for (int s = 1; s <= size; s++)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; s--)
    {
        swap(arr[1], arr[s]);
        const int max_s = s - 1;

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
            {
                c |= 1;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
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

    for (;;)
    {
        std::cin >> N >> M;
        if (N == 0 && M == 0)
        {
            break;
        }

        init();

        for (int i = 1; i <= M; i++)
        {
            Edge& e = EDGES[i];
            std::cin >> e.v1 >> e.v2 >> e.w;

            OLD += e.w;
        }

        sort(EDGES, M);

        for (int i = 1; i <= M; i++)
        {
            const Edge& e = EDGES[i];

            if (find(e.v1) == find(e.v2))
            {
                continue;
            }

            _union(e.v1, e.v2);
            NEW += e.w;
        }

        std::cout << OLD - NEW << '\n';
    }

    return 0;
}
