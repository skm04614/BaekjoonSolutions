#define _CRT_SECURE_NO_WARNINGS

#include <iostream>


struct Element
{
    bool blocker;
};

struct Queue
{
    static constexpr int MAX_SIZE = 500500;
    static constexpr int MAX_ORIENTATION = 4;

    int orientation;
    Element data[MAX_SIZE];
    int lp, rp;

    int e_cnt;
    int b_cnt;

    Queue() : lp{ 0x10000000 }, rp{ 0x10000000 }, data{}, orientation{ 0 }, e_cnt{ 0 }, b_cnt{ 0 }
    {

   }

    void push(bool blocker)
    {
        data[(++rp % MAX_SIZE)].blocker = blocker;

        ++(blocker ? b_cnt : e_cnt);

        gravity();
    }

    void pop()
    {
        if (lp == rp)
        {
            return;
        }

        --(data[++lp % MAX_SIZE].blocker ? b_cnt : e_cnt);

        gravity();
    }

    void cw()
    {
        orientation = (orientation + 1) % MAX_ORIENTATION;
        gravity();
    }

    void ccw()
    {
        orientation = (orientation - 1 + MAX_ORIENTATION) % MAX_ORIENTATION;
        gravity();
    }

    void gravity()
    {
        if (orientation == 1)
        {
            while (lp < rp && !data[(lp + 1) % MAX_SIZE].blocker)
            {
                ++lp;
                --e_cnt;
            }
        }
        else if (orientation == 3)
        {
            while (lp < rp && !data[rp % MAX_SIZE].blocker)
            {
                --rp;
                --e_cnt;
            }
        }
    }
} Q;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char op[50] = "";
    char buf[50] = "";
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> op;
        if (op[0] == 'c')
        {
            char c;
            std::cin >> c;
            std::cout << (c == 'w' ? Q.b_cnt : Q.e_cnt) << '\n';
        }
        else if (op[0] == 'r')
        {
            std::cin >> buf;
            if (buf[0] == 'r')
            {
                Q.cw();
            }
            else
            {
                Q.ccw();
            }
        }
        else if (op[0] == 'p' && op[1] == 'o')
        {
            Q.pop();
        }
        else
        {
            char c;
            std::cin >> c;
            Q.push(c == 'w');
        }
    }

    return 0;
}
