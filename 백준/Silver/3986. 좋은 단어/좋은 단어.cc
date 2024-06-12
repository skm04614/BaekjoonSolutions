#include <cstdio>

int main(void)
{
	int T = 0;
	scanf("%d", &T);
	char word[100001];
	char buf[100001];
	int cnt = 0;
	for (int t = 0; t < T; t++)
	{
		scanf("%s", word);
		int w = 0;
		int b = 0;
		char last = '\0';
		while (word[w])
		{
			if (last != word[w])
			{
				buf[b++] = word[w];
			}
			else
			{
				b--;
			}

			last = b == 0 ? '\0' : buf[b - 1];
			w++;
		}
		
		if (b == 0)
		{
			cnt++;
		}
	}

	printf("%d", cnt);

	return 0;
}