#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int _slen(const char* s)
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

constexpr int L = 200200;

char S[L];
int SA[L];
int LCP[L];
int G[L];
int TMP[L];
int N;
int M;

bool cmp(int sfx1, int sfx2, const int d)
{
    if (G[sfx1] == G[sfx2])
    {
        sfx1 += d;
        sfx2 += d;

        return (sfx1 < N && sfx2 < N) ? G[sfx1] < G[sfx2] : sfx1 > sfx2;
    }

    return G[sfx1] < G[sfx2];
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
    N = _slen(S);
    for (int i = 0; i < N; ++i)
    {
        SA[i] = i;
        G[i] = S[i];
    }

    for (int d = 1; ; d <<= 1)
    {
        sort(SA, N, d);

        TMP[0] = 0;
        for (int i = 1; i < N; ++i)
        {
            TMP[i] = TMP[i - 1] + cmp(SA[i - 1], SA[i], d);
        }

        for (int i = 0; i < N; ++i)
        {
            G[SA[i]] = TMP[i];
        }

        if (TMP[N - 1] == N - 1)
        {
            break;
        }
    }
}

void init_lcp()
{
    int k = 0;
    for (int i = 0; i < N; ++i, k = max(k - 1, 0))
    {
        if (G[i] == 0)
        {
            continue;
        }

        for (int j = SA[G[i] - 1]; S[i + k] == S[j + k]; ++k);
        LCP[G[i]] = k;
    }
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> S;
    
    M = _slen(S);

    S[M] = '#';
    std::cin >> S + M + 1;

    init_sa();
    init_lcp();

    int lc = 0;
    int sidx = 0;
    for (int i = 1; i < N; ++i)
    {
        if ((SA[i] + LCP[i] <= M && M < SA[i - 1]) || (SA[i - 1] + LCP[i] <= M && M < SA[i]))
        {
            if (LCP[i] > lc)
            {
                lc = LCP[i];
                sidx = SA[i];
            }
        }
    }

    std::cout << lc << '\n';
    for (int i = 0; i < lc; ++i)
    {
        std::cout << S[i + sidx];
    }

    return 0;
}