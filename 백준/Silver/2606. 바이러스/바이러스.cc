#include <stdio.h>

int AdjMtrx[101][101];
int NCom;
int Visited[101];

void input(void) {
	scanf("%d", &NCom);
	int nEdge;
	scanf("%d", &nEdge);
	int n1, n2;
	for (int i = 0; i < nEdge; i++) {
		scanf("%d %d", &n1, &n2);
		AdjMtrx[n1][n2] = AdjMtrx[n2][n1] = 1;
	}
	Visited[1] = 1;
}

int DFS(int src, int cnt) {
	int result = 1;
	for (int i = 1; i <= NCom; i++) {
		if (!AdjMtrx[src][i] || Visited[i]) {
			continue;
		}

		Visited[i] = 1;
		result += DFS(i, cnt + 1);
	}

	return result;
}

int main(void) {
	input();

	printf("%d", DFS(1, 0) - 1);

	return 0;
}