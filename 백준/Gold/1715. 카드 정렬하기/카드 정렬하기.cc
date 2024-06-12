#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct MinHeap
{
    int data[100100];
    int _size;

    int size() const
    {
        return _size;
    }

    int peek() const
    {
        return data[1];
    }

    void push(int v)
    {
        data[++_size] = v;

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

    int pop()
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

    int N;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int val;
        std::cin >> val;
        HQ.push(val);
    }

    int res = 0;
    while (HQ.size() > 1)
    {
        int tmp = HQ.pop() + HQ.pop();
        res += tmp;
        HQ.push(tmp);
    }
    std::cout << res;


    return 0;
}
