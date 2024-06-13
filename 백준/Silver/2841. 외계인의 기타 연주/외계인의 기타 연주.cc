#include <cstdio>

int records[7][500001] = {};
int ridx[7] = { -1, -1, -1, -1, -1, -1, -1 };

int main(void)
{
	int N, P;
	scanf("%d %d", &N, &P);

	int s, p;
	int cnt = 0;
	for (int i = 0; i < N; i++)
	{
		scanf("%d %d", &s, &p);
		int& r = ridx[s];

		for (;;)
		{
			if (r == -1 || records[s][r] <= p)
			{
				break;
			}
			r--;
			cnt++;
		}

		if (r == -1 || records[s][r] != p)
		{
			records[s][++r] = p;
			cnt++;
		}
	}

	printf("%d", cnt);

	return 0;
}