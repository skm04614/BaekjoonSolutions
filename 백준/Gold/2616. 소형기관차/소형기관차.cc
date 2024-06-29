#include <iostream>

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int S[50050];
int DP[3][50050];
int N;
int K;

int sol(int depth, int start)
{
    if (depth == 3 || start > N - K + 1)
    {
        return 0;
    }

    if (DP[depth][start])
    {
        return DP[depth][start];
    }

    DP[depth][start] = S[start + K - 1] - S[start - 1] + sol(depth + 1, start + K);
    for (int s = start + 1; s <= N - K + 1; ++s)
    {
        int tmp = sol(depth, s);
        DP[depth][start] = max(DP[depth][start], tmp);
        if (tmp)
        {
            break;
        }
    }
    
    return DP[depth][start];
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        int val;
        std::cin >> val;
        S[i] = S[i - 1] + val;
    }
    std::cin >> K;

    std::cout << sol(0, 1);

    return 0;
}
