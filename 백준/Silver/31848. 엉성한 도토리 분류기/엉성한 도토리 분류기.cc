#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int A[100100];
int N;

int bin_search(int* arr, int idx0, int idx1, int k)
{
    while (idx0 <= idx1)
    {
        int mid = (idx0 + idx1) >> 1;

        if (k <= arr[mid])
        {
            idx1 = mid - 1;
        }
        else
        {
            idx0 = mid + 1;
        }
    }

    return idx0;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    int inc = 0;
    for (int i = 1; i <= n; ++i)
    {
        int val;
        std::cin >> val;
        val += inc++;

        A[++N] = val > A[N] ? val : A[N];
    }

    int s;
    std::cin >> s;
    for (int i = 0; i < s; ++i)
    {
        int k;
        std::cin >> k;
        std::cout << bin_search(A, 1, N, k) << ' ';
    }

    bin_search(A, 1, N, 5);

    return 0;
}
