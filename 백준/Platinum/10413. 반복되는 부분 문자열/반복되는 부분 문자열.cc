#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

inline int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

template <typename T>
inline void swap(T& x, T& y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

char S[100100];
int SA[100100];
int ISA[100100];
int TMP[100100];
int LCP[100100];
int L;

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
    for (int sfx = 0, k = 0; sfx < L; ++sfx, k = max(k - 1, 0))
    {
        if (ISA[sfx] == 0)
        {
            continue;
        }

        for (int sfx2 = SA[ISA[sfx] - 1]; S[sfx + k] == S[sfx2 + k]; ++k);
        LCP[ISA[sfx]] = k;
    }
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> S;

        init_sa();
        init_lcp();

        unsigned long long sol = 0;
        for (int i = 1; i < L; ++i)
        {
            sol += max(LCP[i] - LCP[i - 1], 0);
        }
        std::cout << sol << '\n';
    }

    return 0;
}