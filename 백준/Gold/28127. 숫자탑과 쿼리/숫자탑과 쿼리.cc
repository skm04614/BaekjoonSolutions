#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using ull = unsigned long long;

ull PREFIX[1510];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    for (int i = 2; i < sizeof(PREFIX) / sizeof(PREFIX[0]); ++i)
    {
        PREFIX[i] = PREFIX[i - 1] + (i - 1);
    }
    
    int T;
    std::cin >> T;
    while (T--)
    {
        ull a, b, x;
        std::cin >> a >> b >> x;

        int l = 1;
        int r = (sizeof(PREFIX) / sizeof(PREFIX[0])) - 1;
        for (;;)
        {
            if (l > r)
            {
                break;
            }

            int m = (l + r) >> 1;
            ull val = (a * m) + (b * PREFIX[m]);
            if (x <= val)
            {
                r = m - 1;
            }
            else
            {
                l = m + 1;
            }
        }

        std::cout << l << ' ' << (x - (a * r) - (b * PREFIX[r])) << '\n';
    }

     return 0;
}