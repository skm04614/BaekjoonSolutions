#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char DEC_TO_B36[37] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int B36_TO_DEC[0xFF];

int GAIN[37];

int _slen(const char* s)
{
    int len = 0;
    while (*s++) { ++len; }
    return len;
}

void _srev(char* s)
{
    int len = _slen(s);

    for (int i = 0; i < len / 2; ++i)
    {
        char tmp = s[i];
        s[i] = s[len - 1 - i];
        s[len - 1 - i] = tmp;
    }
}

void init()
{
    int val = 0;
    for (int c = '0'; c <= '9'; ++c)
    {
        B36_TO_DEC[c] = val++;
    }

    for (int c = 'A'; c <= 'Z'; ++c)
    {
        B36_TO_DEC[c] = val++;
    }

    for (int i = 0; i < 36; ++i)
    {
        GAIN[i] = 35 - i;
    }
}

struct B36Cnt
{
    int val[53];

    B36Cnt() : val{}
    {

    }

    void round(int idx)
    {
        int carry = 0;
        while (val[idx] >= 36)
        {
            val[idx + 1] += (val[idx] / 36) + carry;
            val[idx] %= 36;
            ++idx;
        }
    }

    void increment(int idx)
    {
        ++val[idx];
        round(idx);
    }

    B36Cnt operator*(int multiplier) const
    {
        B36Cnt ret = *this;

        int carry = 0;
        for (int idx = 52; idx >= 0; --idx)
        {
            ret.val[idx] *= multiplier;
            ret.round(idx);
        }

        return ret;
    }

    B36Cnt& operator+=(const B36Cnt& other)
    {
        int carry = 0;
        for (int idx = 0; idx < 52; ++idx)
        {
            val[idx] += other.val[idx];
            val[idx + 1] += (val[idx] / 36) + carry;
            val[idx] %= 36;
        }

        return *this;
    }

    bool operator>(const B36Cnt& other) const
    {
        for (int idx = 52; idx >= 0; --idx)
        {
            if (val[idx] == other.val[idx])
            {
                continue;
            }

            return val[idx] > other.val[idx];
        }

        return false;
    }

    void clear()
    {
        for (int idx = 0; idx < 52; ++idx)
        {
            val[idx] = 0;
        }
    }

    void print() const
    {
        int idx = 52;
        while (idx >= 0 && val[idx] == 0)
        {
            --idx;
        }

        if (idx >= 0)
        {
            for (; idx >= 0; --idx)
            {
                std::cout << DEC_TO_B36[val[idx]];
            }
        }
        else
        {
            std::cout << 0;
        }
    }
};

B36Cnt NUMS[37];
B36Cnt GAINS[37];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    init();

    char buf[52];
    int N;
    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        std::cin >> buf;
        _srev(buf);

        const char* ptr = buf;
        for (int idx = 0; *ptr; ++idx, ++ptr)
        {
            NUMS[B36_TO_DEC[*ptr]].increment(idx);
        }
    }

    for (int i = 0; i < 36; ++i)
    {
        GAINS[i] = NUMS[i] * GAIN[i];
    }

    int K;
    std::cin >> K;
    while (K--)
    {
        int max_idx = 0;
        B36Cnt _max = GAINS[0];
        for (int i = 1; i < 36; ++i)
        {
            if (GAINS[i] > _max)
            {
                _max = GAINS[i];
                max_idx = i;
            }
        }

        NUMS[B36_TO_DEC['Z']] += NUMS[max_idx];

        NUMS[max_idx].clear();
        GAINS[max_idx].clear();
    }

    B36Cnt sol;
    for (int i = 0; i < 36; ++i)
    {
        sol += NUMS[i] * i;
    }

    sol.print();


    return 0;
}
