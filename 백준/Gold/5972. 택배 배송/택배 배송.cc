#include <iostream>

constexpr int INF = 0x7FFFFFFF;

int N, M;
int V0, V1;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Edge
{
    int v_dest;
    int w;
    Edge* next;
};

Edge POOL[100100];
Edge* EDGES[50050];

int COST_1[50050];

struct Element
{
    int v;
    int cost;

    bool operator<=(const Element& other) const
    {
        return cost <= other.cost;
    }
};

struct Heap
{
    Element arr[1001000];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(Element e)
    {
        arr[++size] = e;

        int c = size;
        while (c > size)
        {
            int p = c >> 1;
            if (arr[p] <= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    Element pop()
    {
        Element ret = arr[1];
        swap(arr[1], arr[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && arr[c | 1] <= arr[c])
            {
                c |= 1;
            }

            if (arr[p] <= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }
} HQ;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= N; i++)
    {
        COST_1[i] = INF;
    }
    for (int i = 1; i <= M; i++)
    {
        Edge& e1 = POOL[i << 1];
        Edge& e2 = POOL[i << 1 | 1];

        int v0, v1, w;
        std::cin >> v0 >> v1 >> w;

        e1.v_dest = v1;
        e1.w = w;
        e1.next = EDGES[v0];
        EDGES[v0] = &e1;

        e2.v_dest = v0;
        e2.w = w;
        e2.next = EDGES[v1];
        EDGES[v1] = &e2;
    }

    HQ.push({ 1, COST_1[1] = 0 });
    while (!HQ.empty())
    {
        const Element current = HQ.pop();
        if (current.cost > COST_1[current.v])
        {
            continue;
        }

        for (const Edge* e = EDGES[current.v]; e; e = e->next)
        {
            if (COST_1[e->v_dest] <= COST_1[current.v] + e->w)
            {
                continue;
            }

            HQ.push({ e->v_dest, COST_1[e->v_dest] = COST_1[current.v] + e->w });
        }
    }
    std::cout << COST_1[N];

    return 0;
}
