#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Station
{
    int x;
    int f;

    bool smaller_x(const Station& other) const
    {
        return x < other.x;
    }

    bool greater_f(const Station& other) const
    {
        return f > other.f;
    }
};

Station ST[100100];
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

void sort(Station* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (!arr[p].smaller_x(arr[c]))
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
            if ((c | 1) <= max_s && !arr[c | 1].smaller_x(arr[c]))
            {
                c |= 1;
            }

            if (!arr[p].smaller_x(arr[c]))
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
    Station data[100100];
    int _size;

    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

    const Station& peek() const
    {
        return data[1];
    }

    void push(Station e)
    {
        data[++_size] = e;

        int c = _size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p].greater_f(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Station pop()
    {
        swap(data[1], data[_size--]);

        int p = 1;
        int c = p << 1;
        while (c <= _size)
        {
            if ((c | 1) <= _size && data[c | 1].greater_f(data[c]))
            {
                c |= 1;
            }

            if (data[p].greater_f(data[c]))
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
        std::cin >> ST[i].x >> ST[i].f;
    }

    int x, f0;
    std::cin >> x >> f0;

    ST[++N] = { x, 0 };
    sort(ST, N);

    int x0 = 0;
    int cnt = 0;
    for (int i = 1; i <= N; ++i)
    {
        int df = ST[i].x - x0;
        x0 = ST[i].x;
        f0 -= df;

        while (f0 < 0 && !HQ.empty())
        {
            f0 += HQ.pop().f;
            ++cnt;
        }

        if (f0 < 0)
        {
            break;
        }

        HQ.push(ST[i]);
    }

    std::cout << (f0 < 0 ? -1 : cnt);

    return 0;
}
