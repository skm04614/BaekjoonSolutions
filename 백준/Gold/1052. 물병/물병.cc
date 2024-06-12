#include <iostream>

int count_set_bits(int val)
{
    int cnt = 0;
    for (int n = 1; n < val; n <<= 1)
    {
        if (val & n)
        {
            ++cnt;
        }
    }
    return cnt;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int N, K;
    std::cin >> N >> K;

    int sol = 0;
    for (int n = 1; count_set_bits(N) > K; n <<= 1)
    {
        if (N & n)
        {
            N += n;
            sol += n;
        }
    }
    std::cout << sol;

    return 0;
}
