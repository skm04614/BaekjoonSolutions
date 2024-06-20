#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int REC[40040];
int R;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int N;
    std::cin >> N;
    for (int i = 1; i <= N; ++i)
    {
        int val;
        std::cin >> val;

        if (val > REC[R])
        {
            REC[++R] = val;
        }
        else
        {
            int left = 1;
            int right = R;
            while (left <= right)
            {
                int mid = (left + right) >> 1;

                if (val <= REC[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }

            REC[left] = val;
        }
    }

    std::cout << R;

    return 0;
}