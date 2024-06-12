#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>
#include <string>

int main(void)
{
	double a, b;
	scanf("%lf %lf", &a, &b);

	printf("%.13lf", a / b);
	
	return 0;
}