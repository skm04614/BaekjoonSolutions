#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

char SCORE[12] = "FFFFFFDCBAA";

int main(void)
{
	int score;
	scanf("%d", &score);

	printf("%c", SCORE[score / 10]);

	return 0;
}

// 