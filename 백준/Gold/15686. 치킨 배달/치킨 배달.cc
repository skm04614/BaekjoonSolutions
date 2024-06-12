#include <stdio.h>

#define ABS(n) ((n) > 0 ? (n) : -(n))
#define DIST(t1, t2) (ABS(t1.y - t2.y) + ABS(t1.x - t2.x))

typedef struct _Tile {
	int y;
	int x;
	int isClosed;
} Tile;

Tile House[50];
Tile CK[13];
int NH, NC, M;
int Min;

void input(void) {
	int n;
	scanf("%d %d", &n, &M);
	int type;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &type);
			if (type == 2) {
				CK[NC].y = i;
				CK[NC].x = j;
				NC++;
			}
			else if (type == 1) {
				House[NH].y = i;
				House[NH].x = j;
				NH++;
			}
		}
	}
	Min = 0x7FFFFFFF;
}

int ckDistance(void) {
	int total = 0;
	int min, result;
	for (int h = 0; h < NH; h++) {
		min = 0x7FFFFFFF;
		for (int c = 0; c < NC; c++) {
			if (!CK[c].isClosed) {
				result = DIST(CK[c], House[h]);
				min = min < result ? min : result;
			}
		}
		total += min;
	}
	return total;
}

void DFS(int ck, int toClose) {
	if (toClose == 0) {
		int dist = ckDistance();
		if (Min > dist) {
			Min = dist;
		}
		return;
	}

	if (ck == NC) {
		return;
	}
	
	CK[ck].isClosed = 1;
	DFS(ck + 1, toClose - 1);
	CK[ck].isClosed = 0;
	DFS(ck + 1, toClose);
}

int main(void) {
	input();
	DFS(0, NC - M);
	printf("%d", Min);

	return 0;
}