#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

int PARENT[1001];
int N;

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
    int w;

    bool operator>=(const Edge& other) const
    {
        return w >= other.w;
    }
};

void swap(Edge& e1, Edge& e2)
{
    Edge tmp = e1;
    e1 = e2;
    e2 = tmp;
}

struct MinHeap
{
    Edge data[510000];
    int n;

    MinHeap() : data{}, n{ 0 }
    {
    }

    void push(const Edge e)
    {
        data[++n] = e;

        int c = n;
        while (c > 1)
        {
            if (data[c] >= data[c / 2])
            {
                break;
            }
            
            swap(data[c], data[c / 2]);
            c /= 2;
        }
    }

    Edge pop(void)
    {
        Edge ret = data[1];
        swap(data[1], data[n--]);

        int p = 1;
        while (n >= 2 * p)
        {
            int c1 = 2 * p;
            int c2 = c1 + 1;
            int c = c1;
            if (c2 <= n && data[c1] >= data[c2])
            {
                c = c2;
            }

            if (data[c] >= data[p])
            {
                break;
            }

            swap(data[c], data[p]);
            p = c;
        }
        
        return ret;
    }

    bool empty() const
    {
        return n == 0;
    }
};

MinHeap MH;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    int val;
    for (int i = 0; i < N; i++)
    {
        PARENT[i] = i;
        for (int j = 0; j < N; j++)
        {
            std::cin >> val;
            if (i < j)
            {
                MH.push({ i, j, val });
            }
        }
    }
    
    ull sol = 0;
    while (!MH.empty())
    {
        const Edge edge = MH.pop();
        if (find(edge.v1) == find(edge.v2))
        {
            continue;
        }

        _union(edge.v1, edge.v2);
        sol += edge.w;
    }
    std::cout << sol;

    return 0;
}