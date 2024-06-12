#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MOD = 360000;

int C1[200200];
int C2[200200];
int N;

int BUF[400400];
int KEY[200200];
int PMATCH[200200];

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void sort(int* arr, int size)
{
    --arr; // compensate for 0-based arr

    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(arr[1], arr[s]);
        const int max_s = s - 1;
        
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && arr[c | 1] >= arr[c])
            {
                c |= 1;
            }

            if (arr[p] >= arr[c])
            {
                break;
            }

            swap(arr[p], arr[c]);
            p = c;
            c = p << 1;
        }
    }
}

void init_pmatch()
{
    PMATCH[0] = 0;
    int len = 0;
    for (int i = 1; i < N; ++i)
    {
        while (len && KEY[i] != KEY[len])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[i] == KEY[len])
        {
            ++len;
        }

        PMATCH[i] = len;
    }
}

bool find()
{
    int len = 0;
    for (int i = 0; i < 2 * N; ++i)
    {
        while (len && KEY[len] != BUF[i])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[len] == BUF[i])
        {
            ++len;
        }

        if (len == N)
        {
            return true;
        }
    }

    return false;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> C1[i];
    }
    for (int i = 0; i < N; ++i)
    {
        std::cin >> C2[i];
    }

    sort(C1, N);
    sort(C2, N);

    for (int i = 0; i < N; ++i)
    {
        BUF[N + i] = BUF[i] = (C1[i] - C1[(N + i - 1) % N] + MOD) % MOD;
        KEY[i] = (C2[i] - C2[(N + i - 1) % N] + MOD) % MOD;
    }

    init_pmatch();
    std::cout << (find() ? "possible" : "impossible");

    return 0;
}
