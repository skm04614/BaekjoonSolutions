#include <stdio.h>

#define SWAP(e1, e2) {Element temp = (e1); (e1) = (e2); (e2) = temp;}

typedef struct _Element {
	int y;
	int x;
	int t;
} Element;

typedef struct _Queue {
	Element data[20 * 20];
	int rp;
	int wp;
} Queue;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[4] = { {-1, 0}, {0, -1}, {1, 0}, {0, 1} };

int Map[20][20];
int VisitCheck[20][20];
int L;
int SharkSize;
int ExpLeft;
int SharkX, SharkY;
Queue Q;
Element Candidates[20 * 20];

void enqueue(int y, int x, int t) {
	Q.data[Q.wp].y = y;
	Q.data[Q.wp].x = x;
	Q.data[Q.wp].t = t;
	Q.wp++;
}

Element dequeue(void) {
	return Q.data[Q.rp++];
}

int isQEmpty(void) {
	return Q.rp == Q.wp;
}

int isValidCoords(int y, int x) {
	return y >= 0 && y < L && x >= 0 && x < L;
}

void init(void) {
	Q.wp = Q.rp = 0;
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			VisitCheck[i][j] = (Map[i][j] > SharkSize) ? 1 : 0;
		}
	}

	enqueue(SharkY, SharkX, 0);
	Map[SharkY][SharkX] = 0;
	VisitCheck[SharkY][SharkX] = 1;
}

int cmpElement(Element e1, Element e2) {
	if (e1.t != e2.t) {
		return e1.t - e2.t;
	}

	if (e1.y != e2.y) {
		return e1.y - e2.y;
	}

	return e1.x - e2.x;
}

void bubbleSortC(int upper) {
	for (int i = 1; i < upper; i++) {
		for (int j = 0; j < upper - i; j++) {
			if (cmpElement(Candidates[j], Candidates[j + 1]) > 0) {
				SWAP(Candidates[j], Candidates[j + 1]);
			}
		}
	}
}

void input(void) {
	scanf("%d", &L);
	for (int i = 0; i < L; i++) {
		for (int j = 0; j < L; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] == 9) {
				SharkY = i;
				SharkX = j;
			}
		}
	}
	ExpLeft = SharkSize = 2;
}

int BFS(void) {
	int nC = 0;
	while (!isQEmpty()) {
		Element current = dequeue();
		for (int i = 0; i < 4; i++) {
			int ny = current.y + DIRS[i].dy;
			int nx = current.x + DIRS[i].dx;
			if (!VisitCheck[ny][nx] && isValidCoords(ny, nx)) {
				VisitCheck[ny][nx] = 1;
				enqueue(ny, nx, current.t + 1);
				if (Map[ny][nx] && Map[ny][nx] < SharkSize) {
					Candidates[nC++] = Q.data[Q.wp - 1];
				}
			}
		}
	}
	
	if (nC) {
		bubbleSortC(nC);
		Element target = Candidates[0];
		Map[target.y][target.x] = 0;
		SharkY = target.y;
		SharkX = target.x;
		ExpLeft--;
		if (!ExpLeft) {
			SharkSize++;
			ExpLeft = SharkSize;
		}
		return target.t;
	}

	return 0;
}

int main(void) {
	input();

	int timer = 0;
	int result;
	do {
		init();
		result = BFS();
		timer += result;
	} while (result);

	printf("%d", timer);

	return 0;
}