#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void sort(T* arr, int size)
{
    for (int s = 1; s <= size; ++s)
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

    for (int s = size; s >= 1; --s)
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

struct Work
{
    int t;
    int g;

    bool operator>=(const Work& other) const
    {
        return t <= other.t;
    }

    bool higher_p(const Work& other) const
    {
        return g >= other.g;
    }
};

Work WORKS[1010];
int N;

struct MaxHeap
{
    Work data[1010];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(Work w)
    {
        data[++size] = w;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p].higher_p(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Work pop()
    {
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1].higher_p(data[c]))
            {
                c |= 1;
            }

            if (data[p].higher_p(data[c]))
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
        std::cin >> WORKS[i].t >> WORKS[i].g;
    }

    sort(WORKS, N);

    int res = 0;
    int idx = 1;
    for (int d = 1000; d >= 1; --d)
    {
        for (; idx <= N; ++idx)
        {
            const Work& w = WORKS[idx];
            if (w.t < d)
            {
                break;
            }

            HQ.push(w);
        }

        if (HQ.empty())
        {
            continue;
        }

        res += HQ.pop().g;
    }
    std::cout << res;


    return 0;
}