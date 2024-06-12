#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Element
{
    int l;
    int h;
    int r;

    bool operator>=(const Element& other) const
    {
        if (l == other.l)
        {
            return h >= other.h;
        }

        return l < other.l;
    }
};

struct MaxHeap
{
    Element data[100100];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(Element e)
    {
        data[++size] = e;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p] >= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Element pop()
    {
        Element ret = data[1];
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1] >= data[c])
            {
                c |= 1;
            }

            if (data[p] >= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }
};

MaxHeap HQ;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N;
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        int l, h, r;
        std::cin >> l >> h >> r;
        HQ.push({ l, h, r });
    }

    Element curr = { 0, 0, 0x7FFFFFFF };
    while (!HQ.empty())
    {
        Element next = HQ.pop();
        if (next.h == curr.h)
        {
            curr.r = max(curr.r, next.r);
            continue;
        }

        if (next.h > curr.h || next.l == curr.r)
        {
            swap(next, curr);
            std::cout << curr.l << ' ' << curr.h << ' ';
        }

        if (next.r > curr.r)
        {
            next.l = curr.r;
            HQ.push(next);
        }
    }

    return 0;
}