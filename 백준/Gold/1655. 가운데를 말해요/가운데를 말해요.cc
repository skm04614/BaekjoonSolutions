#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

struct Heap
{
    int data[100100];
    int size;
    bool ascending;

    Heap(bool ascending) : ascending{ ascending }, size{}, data{}
    {

    }

    void push(int val)
    {
        data[++size] = val;

        int c = size;
        while (c > 1)
        {
            int p = c >> 1;
            if (ascending == (data[p] <= data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            c = p;
        }
    }

    int pop()
    {
        int ret = data[1];
        swap(data[1], data[size--]);

        int p = 1;
        int c = p << 1;

        while (c <= size)
        {
            if ((c | 1) <= size && ascending == (data[c | 1] <= data[c]))
            {
                c |= 1;
            }

            if (ascending == (data[p] <= data[c]))
            {
                break;
            }

            swap(data[p], data[c]);
            p = c;
            c = p << 1;
        }

        return ret;
    }

    int peek() const
    {
        return data[1];
    }
};

Heap MAX_PQ{ false };
Heap MIN_PQ{ true };


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    MAX_PQ.push(-0x7FFFFFFF);
    MIN_PQ.push(0x7FFFFFFF);

    int N;
    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;

        MAX_PQ.push(val);

        if (MAX_PQ.peek() > MIN_PQ.peek())
        {
            MIN_PQ.push(MAX_PQ.pop());
            MAX_PQ.push(MIN_PQ.pop());
        }

        if (MAX_PQ.size > MIN_PQ.size + 1)
        {
            MIN_PQ.push(MAX_PQ.pop());
        }

        std::cout << MAX_PQ.peek() << '\n';
    }


    return 0;
}