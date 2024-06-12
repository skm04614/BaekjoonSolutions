#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

struct Element
{
    int s;
    int e;

    bool smaller_s(const Element& other) const
    {
        return s < other.s;
    }

    bool smaller_e(const Element& other) const
    {
        return e < other.e;
    }
};

Element C[200200];
int N;

void sort(Element* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (!arr[p].smaller_s(arr[c]))
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);
        const int max_s = s - 1;

        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && !arr[c | 1].smaller_s(arr[c]))
            {
                c |= 1;
            }

            if (!arr[p].smaller_s(arr[c]))
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

struct MinHeap
{
    Element data[200200];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    int getSize() const
    {
        return size;
    }

    const Element& peek() const
    {
        return data[1];
    }

    void push(Element e)
    {
        data[++size] = e;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p].smaller_e(data[c]))
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
            if ((c | 1) <= size && data[c | 1].smaller_e(data[c]))
            {
                c |= 1;
            }

            if (data[p].smaller_e(data[c]))
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

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> C[i].s >> C[i].e;
    }

    sort(C, N);

    int res = 0;
    for (int i = 1; i <= N; ++i)
    {
        const Element& c = C[i];

        while (!HQ.empty() && HQ.peek().e <= c.s)
        {
            HQ.pop();
        }

        HQ.push(c);

        res = max(res, HQ.getSize());
    }
    std::cout << res;

    return 0;
}