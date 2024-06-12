#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

constexpr int MAP[13] = {0, 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };
constexpr int START = 60;
constexpr int END = 334;

inline int min(int x, int y)
{
    return x < y ? x : y;
}

inline int max(int x, int y)
{
    return x > y ? x : y;
}

int REC[366];
int N;

int convert_date(int month, int day)
{
    return MAP[month] + day;
}


int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; ++i)
    {
        int m0, d0, m1, d1;
        std::cin >> m0 >> d0 >> m1 >> d1;

        int cd0 = max(START, convert_date(m0, d0));
        int cd1 = min(END, convert_date(m1, d1 - 1));

        REC[cd0] = max(REC[cd0], cd1);
    }

    int res = 1;
    int left = START;
    int right = REC[left];
    for (;;)
    {
        if (left >= END || right >= END)
        {
            break;
        }

        int tmp = 0;
        for (int i = left; i <= right + 1; ++i)
        {
            tmp = max(tmp, REC[i]);
        }

        if (tmp == 0)
        {
            res = 0;
            break;
        }

        ++res;
        left = right;
        right = tmp;
    }
    std::cout << res;

    return 0;
}
