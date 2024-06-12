#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

template <typename T>
void q_sort(T* arr, int idx0, int idx1)
{
    if (idx0 >= idx1)
    {
        return;
    }

    int pivot = idx0;
    int left = pivot + 1;
    int right = idx1;
    for (;;)
    {
        while (left <= right && arr[right] < arr[pivot])
        {
            --right;
        }

        while (left <= right && arr[left] >= arr[pivot])
        {
            ++left;
        }

        if (left > right)
        {
            swap(arr[pivot], arr[right]);
            break;
        }

        swap(arr[left], arr[right]);
    }

    q_sort(arr, idx0, right - 1);
    q_sort(arr, right + 1, idx1);
}

struct Shark
{
    int a;
    int b;
    int c;

    bool operator>=(const Shark& other) const
    {
        return a >= other.a && b >= other.b && c >= other.c;
    }

    bool operator<(const Shark& other) const
    {
        return !(*this >= other);
    }
};

Shark SHARKS[51];
int N;

struct Adj
{
    int b;
    Adj* next;

    Adj(int b, Adj* next) : b{ b }, next{ next }
    {

    }

    ~Adj()
    {
        delete next;
        next = nullptr;
    }
};

Adj* ADJ[51];
int B[51];
bool VISITED[51];

void reset()
{
    for (int b = 1; b <= N; ++b)
    {
        VISITED[b] = false;
    }
}

bool dfs(int a)
{
    for (const Adj* adj = ADJ[a]; adj; adj = adj->next)
    {
        const int b = adj->b;
        if (VISITED[b])
        {
            continue;
        }
        VISITED[b] = true;

        if (!B[b] || dfs(B[b]))
        {
            B[b] = a;
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
    for (int i = 1; i <= N; ++i)
    {
        Shark& s = SHARKS[i];
        std::cin >> s.a >> s.b >> s.c;
    }

    q_sort(SHARKS, 1, N);

    for (int i = 1; i <= N; ++i)
    {
        for (int j = i + 1; j <= N; ++j)
        {
            if (SHARKS[i] >= SHARKS[j])
            {
                ADJ[i] = new Adj{ j, ADJ[i] }; // a-to-b edge
            }
        }
    }

    int res = N;
    for (int a = 1; a <= N; ++a)
    {
        for (int i = 0; i < 2; ++i)
        {
            reset();
            res -= dfs(a);
        }
    }
    std::cout << (res <= 0 ? 1 : res);

    return 0;
}
