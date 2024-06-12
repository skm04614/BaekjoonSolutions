#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

void s_cpy(char* dest, const char* src)
{
    while (*dest++ = *src++);
}

int s_cmp(const char* s1, const char* s2)
{
    while (*s1 && *s2 && *s1 == *s2)
    {
        ++s1;
        ++s2;
    }
    
    if (*s1 == 0 && *s2 == 0)
    {
        return 0;
    }

    return *s1 < *s2 ? -1 : 1;
}

struct Num
{
    char v[11];
    int size;

    Num() : v{}, size{}
    {

    }

    void set_val(const char* val)
    {
        for (size = 0; val[size]; ++size)
        {
            v[size] = val[size];
        }
        v[size] = 0;
    }

    bool cmp_1(const Num& other) const
    {
        char c1[22]{};
        s_cpy(c1, v);
        s_cpy(c1 + size, other.v);

        char c2[22]{};
        s_cpy(c2, other.v);
        s_cpy(c2 + other.size, v);

        return s_cmp(c1, c2) >= 0;
    }

    bool cmp_2(const Num& other) const
    {
        if (size == other.size)
        {
            return cmp_1(other);
        }

        return size > other.size;
    }

    void print() const
    {
        std::cout << v;
    }

    bool is_null() const
    {
        for (int i = 0; i < size; ++i)
        {
            if (v[i] != '0')
            {
                return false;
            }
        }

        return true;
    }
};

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

void qsort_1(Num* arr, int idx0, int idx1)
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
        while (left <= right && !arr[right].cmp_1(arr[pivot]))
        {
            --right;
        }

        while (left <= right && arr[left].cmp_1(arr[pivot]))
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

    qsort_1(arr, idx0, right - 1);
    qsort_1(arr, right + 1, idx1);
}

void qsort_2(Num* arr, int idx0, int idx1)
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
        while (left <= right && !arr[right].cmp_2(arr[pivot]))
        {
            --right;
        }

        while (left <= right && arr[left].cmp_2(arr[pivot]))
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

    qsort_2(arr, idx0, right - 1);
    qsort_2(arr, right + 1, idx1);
}

Num ARR[55];
int K;
int N;

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    char buf[11]{};
    std::cin >> N >> K;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> buf;
        ARR[i].set_val(buf);
    }

    qsort_2(ARR, 0, N - 1);
    while (N < K)
    {
        ARR[N++] = ARR[0];
    }

    qsort_1(ARR, 0, N - 1);
    for (int i = 0; i < K; ++i)
    {
        ARR[i].print();
    }


    return 0;
}
