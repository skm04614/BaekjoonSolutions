#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>


int main(void)
{
	char buf[1010];
	int i;
	scanf("%s", buf);
	scanf("%d", &i);

	printf("%c", buf[i - 1]);

	return 0;
}