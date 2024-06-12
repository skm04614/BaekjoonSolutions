#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int ARR[100100];
int IDX[100100];
int N;


int LEN[100100];
int REC[100100];
int R;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;
        IDX[val] = i;

    }
    for (int i = 1; i <= N; i++)
    {
        int val;
        std::cin >> val;
        ARR[i] = IDX[val];
    }

    for (int i = 1; i <= N; i++)
    {
        if (ARR[i] > REC[R])
        {
            REC[++R] = ARR[i];
            LEN[i] = R;
        }
        else
        {
            int left = 1;
            int right = R;
            for (;;)
            {
                if (left > right)
                {
                    break;
                }

                int mid = (left + right) >> 1;
                if (ARR[i] < REC[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }
            REC[left] = ARR[i];
            LEN[i] = left;
        }
    }
    std::cout << R;

    return 0;
}