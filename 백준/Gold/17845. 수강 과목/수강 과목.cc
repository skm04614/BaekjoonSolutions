#include <iostream>

int DP[2][10010];

int N, K;

int max(int x, int y)

{

    return x > y ? x : y;

}

int main(void)

{

    std::ios_base::sync_with_stdio(false);

    std::cin.tie(NULL);

    std::cout.tie(NULL);

    std::cin >> N >> K;

    int p = 0;

    int c = 1;

    for (int i = 0; i < K; i++)

    {

        int I, T;

        std::cin >> I >> T;

        for (int t = 0; t < T; t++)

        {

            DP[c][t] = DP[p][t];

        }

        DP[c][T] = max(I, DP[p][T]);

        for (int t = T + 1; t <= N; t++)

        {

            

            DP[c][t] = DP[p][t];

            if (DP[p][t - T])

            {

                DP[c][t] = max(DP[c][t], DP[p][t - T] + I);

            }

        }

        

        p ^= 1;

        c ^= 1;

    }

    

    int sol = 0;

    for (int t = 0; t <= N; t++)

    {

        sol = sol > DP[p][t] ? sol : DP[p][t];

    }

    std::cout << sol;

    

    return 0;

}