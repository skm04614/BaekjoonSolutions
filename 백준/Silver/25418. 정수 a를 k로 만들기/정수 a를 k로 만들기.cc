#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int VISITED[1000100];
int Q[1000100];
int LP, RP;

bool is_out_of_bounds(int val)
{
    return val < 0 || val > 1000000;
}

int move(int opt, int val)
{
    return opt ? val << 1 : val + 1;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int a, b;
    std::cin >> a >> b;
    Q[++RP] = a;
    VISITED[a] = 1;
    while (RP > LP)
    {
        const int c = Q[++LP];
        for (int i = 0; i < 2; ++i)
        {
            const int n = move(i, c);
            if (is_out_of_bounds(n) || VISITED[n])
            {
                continue;
            }

            VISITED[n] = VISITED[c] + 1;
            Q[++RP] = n;
            if (n == b)
            {
                LP = RP;
                break;
            }
        }
    }

    std::cout << VISITED[b] - 1;

    return 0;
}
