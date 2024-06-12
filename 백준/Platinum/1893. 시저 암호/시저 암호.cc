#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

char ORDER[65];
int N;
char ORIGINAL[50100];
char TEXT[500100];

int MAP[0xFF];
int REC[0xFF];
int R;

int BUF[500100];
int B;
int KEY[50100];
int PMATCH[50100];
int K;

void reset()
{
    for (int i = 0; i < sizeof(MAP) / sizeof(MAP[0]); ++i)
    {
        MAP[i] = 0;
        REC[i] = 0;
    }

    R = 0;
}

void init_pmatch()
{
    PMATCH[0] = 0;
    int len = 0;
    for (int i = 1; i < K; ++i)
    {
        while (len && KEY[i] != KEY[len])
        {
            len = PMATCH[len - 1];
        }

        if (KEY[i] == KEY[len])
        {
            ++len;
        }

        PMATCH[i] = len;
    }
}

bool is_unique_match(int shift)
{
    int len = 0;
    int cnt = 0;
    for (int i = 0; i < B; ++i)
    {
        while (len && BUF[i] != (KEY[len] + shift) % N)
        {
            len = PMATCH[len - 1];
        }

        if (BUF[i] == (KEY[len] + shift) % N)
        {
            ++len;
        }

        if (len == K)
        {
            if (++cnt > 1)
            {
                return false;
            }

            len = PMATCH[len - 1];
        }
    }

    return cnt == 1;
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
        reset();

        std::cin >> ORDER >> ORIGINAL >> TEXT;
        N = _slen(ORDER);
        for (int i = 0; i < N; ++i)
        {
            MAP[ORDER[i]] = i;
        }

        K = _slen(ORIGINAL);
        for (int i = 0; i < K; ++i)
        {
            KEY[i] = MAP[ORIGINAL[i]];
        }

        B = _slen(TEXT);
        for (int i = 0; i < B; ++i)
        {
            BUF[i] = MAP[TEXT[i]];
        }

        init_pmatch();

        for (int shift = 0; shift < N; ++shift)
        {
            if (is_unique_match(shift))
            {
                REC[R++] = shift;
            }
        }

        if (R == 0)
        {
            std::cout << "no solution";
        }
        else
        {
            std::cout << (R == 1 ? "unique: " : "ambiguous: ");
        }

        for (int i = 0; i < R; ++i)
        {
            std::cout << REC[i] << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}