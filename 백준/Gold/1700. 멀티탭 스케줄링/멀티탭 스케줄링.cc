#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

struct Queue
{
    int data[110];
    int lp;
    int rp;

    bool empty() const
    {
        return lp == rp;
    }

    void push(int v)
    {
        data[++rp] = v;
    }

    int pop()
    {
        return data[++lp];
    }

    int peek() const
    {
        return data[lp + 1];
    }
};

Queue Q[101];
bool USED[101];
int U;

int ORDER[101];
int K;

int N;


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N >> K;
    int sidx = 0;
    for (int i = 0; i < K; ++i)
    {
        std::cin >> ORDER[i];

        if (U < N)
        {
            if (USED[ORDER[i]] == false)
            {
                ++U;
            }
            USED[ORDER[i]] = true;
            sidx = i + 1;
        }
        else
        {
            Q[ORDER[i]].push(i);
        }
    }

    int res = 0;
    for (int i = sidx; i < K; ++i)
    {
        int order = ORDER[i];

        Q[order].pop();

        if (USED[order])
        {
            continue;
        }

        int max_idx = 0;
        int j = 0;
        for (int k = 0; k <= K; ++k)
        {
            if (USED[k] == false)
            {
                continue;
            }

            if (Q[k].empty())
            {
                j = k;
                break;
            }

            if (Q[k].peek() > max_idx)
            {
                max_idx = Q[k].peek();
                j = k;
            }
        }

        ++res;
        USED[j] = false;
        USED[order] = true;
    }
    std::cout << res;

    return 0;
}