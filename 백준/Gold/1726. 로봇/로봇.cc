#include <stdio.h>

#define Q_SIZE 40000

typedef struct _Element {
	int y;
	int x;
	int d;
	int t;
} Element;

typedef struct _Queue {
	Element e[Q_SIZE];
	int wp;
	int rp;
} Queue;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[5] = { {0, 0}, {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

int Map[101][101];
int VC[5][101][101];
int NRow, NCol;
Queue Q;
Element Start, End;

int isQEmpty(void) {
	return Q.rp == Q.wp;
}

void enqueue(int d, int y, int x, int t) {
	Q.e[Q.wp % Q_SIZE].d = d;
	Q.e[Q.wp % Q_SIZE].y = y;
	Q.e[Q.wp % Q_SIZE].x = x;
	Q.e[Q.wp % Q_SIZE].t = t;
	Q.wp++;
}

Element dequeue(void) {
	return Q.e[Q.rp++ % Q_SIZE];
}

int turnLeft(int d) {
	switch (d) {
	case 1:
		return 4;
	case 4:
		return 2;
	case 2:
		return 3;
	case 3:
		return 1;
	default:
		return -1;
	}
}

int turnRight(int d) {
	switch (d) {
	case 1:
		return 3;
	case 3:
		return 2;
	case 2:
		return 4;
	case 4:
		return 1;
	default:
		return -1;
	}
}

int isOutOfBound(int y, int x) {
	return y < 1 || y > NRow || x < 1 || x > NCol;
}

void input(void) {
	scanf("%d %d", &NRow, &NCol);
	for (int i = 1; i <= NRow; i++) {
		for (int j = 1; j <= NCol; j++) {
			scanf("%d", &Map[i][j]);
			for (int d = 1; d <= 4; d++) {
				VC[d][i][j] = Map[i][j];
			}
		}
	}
	scanf("%d %d %d", &Start.y, &Start.x, &Start.d);
	scanf("%d %d %d", &End.y, &End.x, &End.d);
}

int BFS(void) {
	enqueue(Start.d, Start.y, Start.x, 0);
	VC[Start.d][Start.y][Start.x] = 1;
	int ny, nx, nd;
	while (!isQEmpty()) {
		Element curr = dequeue();

		if (curr.y == End.y && curr.x == End.x && curr.d == End.d) {
			return curr.t;
		}

		for (int k = 1; k <= 3; k++) {
			ny = curr.y + k * DIRS[curr.d].dy;
			nx = curr.x + k * DIRS[curr.d].dx;

			if (isOutOfBound(ny, nx) || Map[ny][nx]) {
				break;
			}

			if (VC[curr.d][ny][nx]) {
				continue;
			}

			VC[curr.d][ny][nx] = 1;
			enqueue(curr.d, ny, nx, curr.t + 1);
		}
		for (int j = 0; j < 2; j++) {
			if (j == 0) {
				nd = turnLeft(curr.d);
			}
			else {
				nd = turnRight(curr.d);
			}
			if (VC[nd][curr.y][curr.x]) {
				continue;
			}
			VC[nd][curr.y][curr.x] = 1;
			enqueue(nd, curr.y, curr.x, curr.t + 1);
		}

	}
	return -1;
}

int main(void) {
	input();
	printf("%d", BFS());

	return 0;
}