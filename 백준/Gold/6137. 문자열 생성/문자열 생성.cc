#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

char S[2020];
char T[2020];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int L;
    std::cin >> L;
    for (int i = 0; i < L; ++i)
    {
        std::cin >> S[i];
    }

    int l = 0;
    int r = L - 1;
    for (int i = 0; i < L; ++i)
    {
        int _l = l;
        int _r = r;
        while (S[_l] == S[_r])
        {
            if (_l + 1 >= _r - 1)
            {
                break;
            }

            ++_l;
            --_r;
        }

        if (S[_l] <= S[_r])
        {
            T[i] = S[l++];
        }
        else
        {
            T[i] = S[r--];
        }
    }

    for (int i = 0; i < L; ++i)
    {
        std::cout << T[i];
        if (i && (i + 1) % 80 == 0)
        {
            std::cout << '\n';
        }
    }


    return 0;
}
