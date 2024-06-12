#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char RAW[10][25];
int RAW_LEN[10];
int N;

char KEYS[40500][250];
int PMATCH[250];
int M;
int L;

int K;

int s_len(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

void s_cpy(char* dest, const char* src)
{
    while (*dest++ = *src++);
}

void prep_keys(char* buf, int offset, int visited)
{
    if (visited == (1 << N) - 1)
    {
        s_cpy(KEYS[M++], buf);
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        if (visited & (1 << i))
        {
            continue;
        }

        s_cpy(buf + offset, RAW[i]);
        prep_keys(buf, offset + RAW_LEN[i], visited | (1 << i));
    }
}

bool is_magic_word(const char* key)
{
    PMATCH[0] = 0;

    int len = 0;
    for (int i = 1; i < L; ++i)
    {
        while (len && key[i] != key[len])
        {
            len = PMATCH[len - 1];
        }

        if (key[i] == key[len])
        {
            ++len;
        }

        PMATCH[i] = len;
    }

    int k = 1;
    len = PMATCH[L - 1];
    for (int i = L; i < 2 * L - 1; ++i)
    {
        while (len && key[i % L] != key[len])
        {
            len = PMATCH[len - 1];
        }

        if (key[i % L] == key[len])
        {
            ++len;
        }

        if (len == L)
        {
            ++k;
            len = PMATCH[len - 1];
        }
    }

    return k == K;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> RAW[i];
        RAW_LEN[i] = s_len(RAW[i]);
        L += RAW_LEN[i];
    }

    char buf[250] = "";
    prep_keys(buf, 0, 0);

    std::cin >> K;

    int res = 0;
    for (int i = 0; i < M; ++i)
    {
        res += is_magic_word(KEYS[i]);
    }
    std::cout << res;
    
    return 0;
}
