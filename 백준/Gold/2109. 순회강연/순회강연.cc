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
void _qsort(T* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = idx0 + 1;
    int right = idx1;

    for (;;)
    {
        while (left <= right && arr[right] <= arr[pivot])
        {
            --right;
        }

        while (left <= right && arr[left] >= arr[pivot])
        {
            ++left;
        }

        if (left > right)
        {
            swap(arr[right], arr[pivot]);
            break;
        }

        swap(arr[left], arr[right]);
    }

    _qsort(arr, idx0, right - 1);
    _qsort(arr, right + 1, idx1);
}

struct Lecture
{
    int p;
    int d;

    bool operator>=(const Lecture& other) const
    {
        return d >= other.d;
    }

    bool operator<=(const Lecture& other) const
    {
        return d <= other.d;
    }

    bool higher_p(const Lecture& other) const
    {
        return p > other.p;
    }
};

Lecture LECTURES[10010];
int N;

struct MaxHeap
{
    Lecture data[10010];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    const Lecture& peek() const
    {
        return data[1];
    }

    void push(Lecture lec)
    {
        data[++size] = lec;

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

    Lecture pop()
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
        std::cin >> LECTURES[i].p >> LECTURES[i].d;
    }

    _qsort(LECTURES, 1, N);

    int res = 0;
    int n = 1;
    for (int d = 10000; d >= 1; --d)
    {
        while (n <= N && LECTURES[n].d == d)
        {
            HQ.push(LECTURES[n++]);
        }

        if (HQ.empty())
        {
            continue;
        }

        res += HQ.pop().p;
    }
    std::cout << res;


    return 0;
}
