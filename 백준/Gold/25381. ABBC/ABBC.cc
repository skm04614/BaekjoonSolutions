#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Queue
{
    int data[300300];
    int rp;
    int lp;

    void reset()
    {
        rp = lp = 0;
    }

    void push(int val)
    {
        data[++rp] = val;
    }

    int pop()
    {
        return data[++lp];
    }

    int peek()
    {
        return data[lp + 1];
    }

    bool empty()
    {
        return rp == lp;
    }
};

char BUF[300300];
int B;
Queue Q[4];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> BUF;

    for (B = 0; BUF[B]; ++B)
    {
        const int c = BUF[B] - 'A';

        Q[c].push(B);
    }

    int res = 0;
    while (!Q[1].empty() && ! Q[2].empty())
    {
        if (Q[1].peek() < Q[2].peek())
        {
            ++res;
            Q[1].pop();
            Q[2].pop();
        }
        else
        {
            Q[2].pop();
        }
    }

    while (!Q[1].empty())
    {
        Q[3].push(Q[1].pop());
    }

    while (!Q[0].empty() && !Q[3].empty())
    {
        if (Q[0].peek() < Q[3].peek())
        {
            ++res;
            Q[0].pop();
            Q[3].pop();
        }
        else
        {
            Q[3].pop();
        }
    }

    std::cout << res;

    return 0;
}
