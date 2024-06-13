#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Element
{
    int a;
    int b;

    bool operator<=(const Element& other) const
    {
        if (a == other.a)
        {
            return b <= other.b;
        }

        return a < other.a;
    }
};

struct Heap
{
    Element data[1010];
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
            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Element pop()
    {
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1] <= data[c])
            {
                c |= 1;
            }

            if (data[p] <= data[c])
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return data[size + 1];
    }
} HQ;


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {        
        int n, m;
        std::cin >> n >> m;
        while (m--)
        {
            int a, b;
            std::cin >> a >> b;
            HQ.push({ a, b });
        }

        int cnt = 0;
        int x = 0;
        while (!HQ.empty())
        {
            Element e = HQ.pop();
            if (e.b <= x)
            {
                continue;
            }

            if (e.a > x)
            {
                x = e.a;
                ++cnt;
                continue;
            }

            e.a = x + 1;
            HQ.push(e);
        }

        std::cout << cnt << '\n';
    }

    return 0;
}
