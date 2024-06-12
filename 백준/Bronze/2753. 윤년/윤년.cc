#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int main(void)
{
	int year;
	scanf("%d", &year);

	printf("%d", (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
	
	return 0;
}