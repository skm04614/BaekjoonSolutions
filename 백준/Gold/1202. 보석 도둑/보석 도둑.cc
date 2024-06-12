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

struct Jewel
{
    int v;
    int w;

    bool operator>=(const Jewel& other) const
    {
        return w >= other.w;
    }

    bool more_valuable(const Jewel& other) const
    {
        return v >= other.v;
    }
};

struct MaxValHeap
{
    Jewel data[300300];
    int size;

    bool empty() const
    {
        return size == 0;
    }

    void push(Jewel j)
    {
        data[++size] = j;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (data[p].more_valuable(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    Jewel pop()
    {
        Jewel ret = data[1];

        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;
        while (c <= size)
        {
            if ((c | 1) <= size && data[c | 1].more_valuable(data[c]))
            {
                c |= 1;
            }

            if (data[p].more_valuable(data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }
} HQ;

int BAGS[300300];
int B;

Jewel JEWELS[300300];
int J;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> J >> B;
    for (int i = 1; i <= J; ++i)
    {
        std::cin >> JEWELS[i].w >> JEWELS[i].v;
    }

    for (int i = 1; i <= B; ++i)
    {
        std::cin >> BAGS[i];
    }
    
    sort(JEWELS, J);
    sort(BAGS, B);

    int j = 1;
    unsigned long long sol = 0;
    for (int i = 1; i <= B; ++i)
    {
        const int b = BAGS[i];

        while (j <= J && JEWELS[j].w <= b)
        {
            HQ.push(JEWELS[j++]);
        }

        if (HQ.empty())
        {
            continue;
        }

        sol += HQ.pop().v;
    }
    std::cout << sol;

    return 0;
}