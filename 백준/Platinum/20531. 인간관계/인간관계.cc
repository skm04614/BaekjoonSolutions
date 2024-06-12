#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

constexpr ull MOD = 1000000007;

int PARENT[5050];
ull BELL[5050][5050];
ull SOL[5050];
int N;
int K;

int find(int v)
{
    if (v == PARENT[v])
    {
        return v;
    }

    return PARENT[v] = find(PARENT[v]);
}

void _union(int v1, int v2)
{
    v1 = find(v1);
    v2 = find(v2);

    if (v1 == v2)
    {
        return;
    }

    --K;

    if (v1 < v2)
    {
        PARENT[v2] = v1;
    }
    else
    {
        PARENT[v1] = v2;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int i = 1; i <= 5000; ++i)
    {
        PARENT[i] = i;

        BELL[i][1] = SOL[i] = 1;
        for (int j = 2; j <= i; ++j)
        {
            BELL[i][j] = (BELL[i - 1][j - 1] + j * BELL[i - 1][j]) % MOD;
            SOL[i] = (SOL[i] + BELL[i][j]) % MOD;
        }
    }

    std::cin >> N;
    K = N;

    int Q;
    std::cin >> Q;
    while (Q--)
    {
        int v1, v2;
        std::cin >> v1 >> v2;
        _union(v1, v2);
        std::cout << SOL[K] << '\n';
    }

    return 0;
}