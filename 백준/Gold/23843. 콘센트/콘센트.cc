#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull ARR[10010];
int N, M;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void sort(ull* arr, int size)
{
    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
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

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);

        const int max_s = s - 1;
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] <= arr[c])
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
    }
}

struct Heap
{
    ull data[10010];
    int _size;

    bool empty() const
    {
        return _size == 0;
    }

    int size() const
    {
        return _size;
    }

    const ull& peek() const
    {
        return data[1];
    }

    void push(ull e)
    {
        data[++_size] = e;

        int c = _size;
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

    ull pop()
    {
        swap(data[1], data[_size--]);

        int p = 1;
        int c = p << 1;
        while (c <= _size)
        {
            if ((c | 1) <= _size && data[c | 1] <= data[c])
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

        return data[_size + 1];
    }
} HQ;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    sort(ARR, N);

    for (int i = 1; i <= N; ++i)
    {
        if (HQ.size() < M)
        {
            HQ.push(ARR[i]);
            continue;
        }

        HQ.push(HQ.pop() + ARR[i]);
    }

    ull v = 0;
    while (!HQ.empty())
    {
        v = HQ.pop();
    }
    std::cout << v;

    return 0;
}
