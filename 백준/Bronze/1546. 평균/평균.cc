#define _CRT_SECURE_NO_WARNINGS


#include <cstdio>

int SCORES[1010];

int main(void)
{
	int n;
	int max_score = 0;

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &SCORES[i]);
		max_score = max_score > SCORES[i] ? max_score : SCORES[i];
	}

	int total_score = 0;
	for (int i = 0; i < n; i++)
	{
		total_score += SCORES[i];
	}

	printf("%lf", 100 * static_cast<double>(total_score) / max_score / n);

	return 0;
}