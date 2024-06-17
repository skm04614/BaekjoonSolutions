#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char EQ[25];
int L;

inline int ctoi(char c)
{
    if (c == 0)
    {
        return 0;
    }

    return c - '0';
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int evaluate(int n1, char op, int n2)
{
    if (op == 0)
    {
        return n1;
    }

    if (op == '+')
    {
        return n1 + n2;
    }

    if (op == '*')
    {
        return n1 * n2;
    }

    return n1 - n2;
}

int sol(int idx, int v1, char op1, int v2, char op2, int v3, bool last_rhs)
{
    if (op2 == 0)
    {
        return evaluate(v1, op1, v2);
    }

    const int lhs = evaluate(v1, op1, v2);
    const int rhs = evaluate(v2, op2, v3);

    int res = sol(idx + 2, lhs, op2, v3, EQ[idx], ctoi(EQ[idx + 1]), false);

    if (!last_rhs)
    {
        res = max(res, sol(idx + 2, v1, op1, rhs, EQ[idx], ctoi(EQ[idx + 1]), true));
    }

    return res;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    std::cin >> L >> EQ;
    std::cout << sol(5, ctoi(EQ[0]), EQ[1], ctoi(EQ[2]), EQ[3], ctoi(EQ[4]), false);

    return 0;
}
