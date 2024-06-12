#include <iostream>

using ull = unsigned long long;
constexpr ull MOD = 1000000007;

ull FIB[1000010];
ull X[1000010];
int N;

void init()
{
    FIB[1] = 1;
    for (int n = 2; n <= 1000005; n++)
    {
        FIB[n] = (FIB[n - 1] + FIB[n - 2]) % MOD;
    }
}

void query(int l, int r)
{
    X[l] = (X[l] + FIB[1]) % MOD;
    X[r + 1] = (X[r + 1] + (2 * MOD) - FIB[r - l + 2]) % MOD;
    X[r + 2] = (X[r + 2] + (2 * MOD) - FIB[r - l + 1]) % MOD;
}

void sol()
{
    std::cout << X[1] << ' ';
    for (int n = 2; n <= N; n++)
    {
        X[n] = (X[n] + X[n - 1] + X[n - 2]) % MOD;
        std::cout << X[n] << ' ';
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    int Q;
    std::cin >> N >> Q;
    while (Q--)
    {
        int l, r;
        std::cin >> l >> r;
        query(l, r);
    }

    sol();

    return 0;
}
