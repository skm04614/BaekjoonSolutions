#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

struct Connection
{
    int src;
    int dest;

    bool operator>=(const Connection& other)
    {
        return src >= other.src;
    }
};

void sort(Connection* arr, int size)
{
    for (int s = 1; s <= size; s++)
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

    for (int s = size; s >= 1; s--)
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

Connection ARR[100100];
int LEN[100100];
int N;

int REC[100100];
int R;
int DISCONNECTED[100100];
int D;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 1; i <= N; i++)
    {
        std::cin >> ARR[i].src >> ARR[i].dest;
    }

    sort(ARR, N);

    for (int i = 1; i <= N; i++)
    {
        Connection& c = ARR[i];
        if (c.dest > REC[R])
        {
            REC[++R] = c.dest;
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
                if (c.dest <= REC[mid])
                {
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }

            REC[left] = c.dest;
            LEN[i] = left;
        }
    }

    int max_len = 0;
    for (int i = 1; i <= N; i++)
    {
        max_len = max_len > LEN[i] ? max_len : LEN[i];
    }
    std::cout << N - max_len << '\n';

    int len = max_len;
    for (int i = N; i >= 0; i--)
    {
        if (LEN[i] == len)
        {
            len--;
            continue;
        }

        DISCONNECTED[++D] = ARR[i].src;
    }

    for (int i = D; i >= 1; i--)
    { 
        std::cout << DISCONNECTED[i] << '\n';
    }

    return 0;
}