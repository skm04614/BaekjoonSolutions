#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAX_SIZE = 100'100;

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

char S[MAX_SIZE];
int SA[MAX_SIZE];
int ISA[MAX_SIZE];
int LCP[MAX_SIZE];
int TMP[MAX_SIZE];
int L;

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

bool cmp(int sfx1, int sfx2, const int d)
{
    if (ISA[sfx1] == ISA[sfx2])
    {
        sfx1 += d;
        sfx2 += d;
        return (sfx1 < L && sfx2 < L) ? (ISA[sfx1] < ISA[sfx2]) : (sfx1 > sfx2);
    }

    return ISA[sfx1] < ISA[sfx2];
}

void sort(int* sa, int size, const int d)
{
    --sa; // compensate for 0-based sa

    for (int s = 1; s <= size; ++s)
    {
        int c = s;
        while (c > 1)
        {
            int p = c >> 1;
            if (!cmp(sa[p], sa[c], d))
            {
                break;
            }

            swap(sa[p], sa[c]);
            c = p;
        }
    }

    for (int s = size; s >= 1; --s)
    {
        swap(sa[1], sa[s]);

        const int max_s = s - 1;
        int p = 1;
        int c = p << 1;
        while (c <= max_s)
        {
            if ((c | 1) <= max_s && !cmp(sa[c | 1], sa[c], d))
            {
                c |= 1;
            }

            if (!cmp(sa[p], sa[c], d))
            {
                break;
            }

            swap(sa[p], sa[c]);
            p = c;
            c = p << 1;
        }
    }
}

void init_sa()
{
    L = _slen(S);
    for (int i = 0; i < L; ++i)
    {
        SA[i] = i;
        ISA[i] = S[i];
    }

    for (int d = 1; ; d <<= 1)
    {
        sort(SA, L, d);

        TMP[0] = 0;
        for (int i = 1; i < L; ++i)
        {
            TMP[i] = TMP[i - 1] + cmp(SA[i - 1], SA[i], d);
        }

        for (int i = 0; i < L; ++i)
        {
            ISA[SA[i]] = TMP[i];
        }

        if (TMP[L - 1] == L - 1)
        {
            break;
        }
    }
}

void init_lcp()
{
    for (int i = 0, k = 0; i < L; ++i, k = max(k - 1, 0))
    {
        if (ISA[i] == 0)
        {
            continue;
        }

        for (int j = SA[ISA[i] - 1]; S[i + k] == S[j + k]; ++k);
        LCP[ISA[i]] = k;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> S;
    init_sa();
    init_lcp();

    int idx = 0;
    int cnt = 0;
    for (int i = 0; i < L; ++i)
    {
        if (LCP[i] > cnt)
        {
            cnt = LCP[i];
            idx = SA[i];
        }
    }
    S[idx + cnt] = 0;

    std::cout << S + idx;

    return 0;
}
