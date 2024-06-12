#include <stdio.h>

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

typedef struct _DCurve {
	int y;
	int x;
	int generation;
	int size;
	int dirIDs[1025];
} DCurve;

const Direction DIRS[4] = { {0, 1}, {-1, 0}, {0, -1}, {1, 0} };

int Map[101][101];
DCurve DCurves[20];
int N;

void input(void) {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &DCurves[i].x);
		scanf("%d", &DCurves[i].y);
		scanf("%d", &DCurves[i].dirIDs[0]);
		scanf("%d", &DCurves[i].generation);
		DCurves[i].size = 1;
		for (int g = 1; g <= DCurves[i].generation; g++) {
			int size = DCurves[i].size;
			for (int j = 0; j < size; j++) {
				DCurves[i].dirIDs[size + j] = (DCurves[i].dirIDs[size - 1 - j] + 1) % 4;
			}
			DCurves[i].size = 2 * DCurves[i].size;
		}
	}
}

void drawOnMap(void) {
	for (int n = 0; n < N; n++) {
		int y = DCurves[n].y;
		int x = DCurves[n].x;
		Map[y][x] = 1;
		for (int i = 0; i < DCurves[n].size; i++) {
			y += DIRS[DCurves[n].dirIDs[i]].dy;
			x += DIRS[DCurves[n].dirIDs[i]].dx;
			Map[y][x] = 1;
		}
	}
}

int isSQ(int y, int x) {
	return Map[y][x] && Map[y + 1][x] && Map[y][x + 1] && Map[y + 1][x + 1];
}

int countSQ(void) {
	int count = 0;
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			count += isSQ(i, j);
		}
	}
	return count;
}

int main(void) {
	input();
	drawOnMap();
	printf("%d", countSQ());

	return 0;
}