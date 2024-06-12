#include <cstdio>

int gStack[100001];
int gStackIdx = -1;
char gRecord[1000001];
int gRecIdx;

int main(void)
{
	int n{};
	scanf("%d", &n);
	int num = 1;
	int tgt{};
	bool is_success = true;

	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tgt);

		while (tgt >= num)
		{
			gStack[++gStackIdx] = num++;
			gRecord[gRecIdx++] = '+';
		}

		if (gStack[gStackIdx] == tgt)
		{
			gStackIdx--;
			gRecord[gRecIdx++] = '-';
		}
		else
		{
			is_success = false;
			break;
		}
	}

	if (is_success)
	{
		for (int i = 0; i < gRecIdx; i++)
		{
			printf("%c\n", gRecord[i]);
		}
	}
	else
	{
		printf("NO");
	}

	return 0;
}