#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Element
{
    int d;
    int s;

    bool smaller_d(const Element& other) const
    {
        return d < other.d;
    }

    bool greater_s(const Element& other) const
    {
        return s > other.s;
    }
};

Element ARR[200200];
int N;

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

void sort(Element* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p].smaller_d(arr[c]))
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
            if ((c | 1) <= max_s && arr[c | 1].smaller_d(arr[c]))
            {
                c |= 1;
            }

            if (arr[p].smaller_d(arr[c]))
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

struct Heap
{
    Element data[200200];
    int _size;

    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

    const Element& peek() const
    {
        return data[1];
    }

    void push(Element e)
    {
        data[++_size] = e;

        int c = _size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p].greater_s(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Element pop()
    {
        swap(data[1], data[_size--]);

        int p = 1;
        int c = p << 1;
        while (c <= _size)
        {
            if ((c | 1) <= _size && data[c | 1].greater_s(data[c]))
            {
                c |= 1;
            }

            if (data[p].greater_s(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return data[_size + 1];
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
        std::cin >> ARR[i].d >> ARR[i].s;
    }

    sort(ARR, N);

    int res = 0;
    int n = 1;
    for (int d = N; d >= 1; --d)
    {
        while (n <= N && ARR[n].d == d)
        {
            HQ.push(ARR[n++]);
        }

        if (HQ.empty())
        {
            continue;
        }

        res += HQ.pop().s;
    }

    std::cout << res;

    return 0;
}
