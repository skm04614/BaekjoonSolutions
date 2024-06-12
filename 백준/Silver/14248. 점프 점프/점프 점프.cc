#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int STEP[100100];
int VISITED[100100];
int N;

int Q[1001000];
int LP;
int RP;


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> STEP[i];
    }

    int S;
    std::cin >> S;

    VISITED[S] = 1;
    Q[++RP] = S;
    while (RP > LP)
    {
        const int c = Q[++LP];
        int step = STEP[c];

        for (int i = 0; i < 2; ++i, step *= -1)
        {
            const int n = c + step;
            if (n <= 0 || n > N || VISITED[n])
            {
                continue;
            }

            VISITED[n] = VISITED[c] + 1;
            Q[++RP] = n;
        }
    }
    std::cout << RP;

    return 0;
}
