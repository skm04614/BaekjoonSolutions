#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[10010];
int N;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

void sort(int* arr, int size)
{
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

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        std::cin >> ARR[i];
    }

    sort(ARR, N);

    unsigned long long sol = 0;
    for (int i = 1; i <= N - 2; ++i)
    {
        int tgt = ARR[i];
        int l = i + 1;
        int r = N;

        while (l < r)
        {
            int sum = ARR[l] + ARR[r];
            if (-tgt == sum)
            {
                unsigned long long nr = 1;
                while (l < r && ARR[r] == ARR[r - 1])
                {
                    ++nr;
                    --r;
                }

                unsigned long long nl = 1;
                while (l < r && ARR[l] == ARR[l + 1])
                {
                    ++nl;
                    ++l;
                }

                if (l == r)
                {
                    while (--nr)
                    {
                        sol += nr;
                    }
                }
                else
                {
                    sol += nr * nl;
                    --r;
                }
            }
            else if (-tgt < sum)
            {
                --r;
            }
            else
            {
                ++l;
            }
        }
    }
    std::cout << sol;

    return 0;
}