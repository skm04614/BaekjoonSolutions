#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

int CARDS[100100];
int N;
bool CARD_EXISTS[10010000];
int SCORE[1001000];

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        std::cin >> CARDS[i];
        CARD_EXISTS[CARDS[i]] = true;
    }

    for (int i = 0; i < N; i++)
    {
        int card = CARDS[i];
        for (int m = 2; m * card <= 1000000; m++)
        {
            if (CARD_EXISTS[m * card])
            {
                SCORE[card]++;
                SCORE[m * card]--;
            }
        }
    }

    for (int i = 0; i < N; i++)
    {
        std::cout << SCORE[CARDS[i]] << ' ';
    }

    return 0;
}