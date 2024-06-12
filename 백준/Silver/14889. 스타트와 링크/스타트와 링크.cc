#include <stdio.h>

#define ABS(x) ((x) > 0 ? (x) : -(x))
#define MIN(x, y) ((x) < (y) ? (x) : (y))

int Synergy[20][20];
int N;
int Team[20];
int Min = 0x7FFFFFFF;

void input(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Synergy[i][j]);
		}
	}
}

int calcSyn(void) {
	int result = 0;
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (Team[i] == 0 && Team[j] == 0) {
				result += (Synergy[i][j] + Synergy[j][i]);
			}
			if (Team[i] == 1 && Team[j] == 1) {
				result -= (Synergy[i][j] + Synergy[j][i]);
			}
		}
	}
	return ABS(result);
}

void DFS(int start, int t1) {
	if (t1 == N / 2) {
		Min = MIN(Min, calcSyn());
		return;
	}
	
	if (start == N) {
		return;
	}
	
	Team[start] = 1;
	DFS(start + 1, t1 + 1);
	Team[start] = 0;

	DFS(start + 1, t1);
}

int main(void) {
	input();
	DFS(0, 0);
	printf("%d", Min);

	return 0;
}