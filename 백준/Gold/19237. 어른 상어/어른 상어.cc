#include <stdio.h>

#define Q_SIZE 100000

typedef struct _Tile {
	int y;
	int x;
} Tile;

typedef struct _Shark {
	int y;
	int x;
	int dir;
	int isDead;
	int dPref[5][4];
} Shark;

typedef struct _Element {
	int y;
	int x;
	int id;
	int expireAt;
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

const Direction DIRS[5] = { {0, 0}, {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

int Map[20][20];
int SCount[20][20];
int Territory[20][20];
int N;
int SDuration;

Shark Sharks[401]; //1부터
Tile newT[401];
int NS;
int NAlive;

Queue Q;

int isQEmpty(void) {
	return Q.wp == Q.rp;
}

void enqueue(int y, int x, int id, int expireAt) {
	Q.e[Q.wp % Q_SIZE].y = y;
	Q.e[Q.wp % Q_SIZE].x = x;
	Q.e[Q.wp % Q_SIZE].id = id;
	Q.e[Q.wp % Q_SIZE].expireAt = expireAt;
	Q.wp++;
}

Element dequeue(void) {
	return Q.e[Q.rp++ % Q_SIZE];
}

int isOutOfBound(int y, int x) {
	return y < 0 || y >= N || x < 0 || x >= N;
}

void addSmell(int y, int x, int id, int expireAt) {
	enqueue(y, x, id, expireAt);
	Territory[y][x] = id;
	SCount[y][x]++;
}

void removeSmell(int currTime) {
	Element curr;
	while (!isQEmpty() && Q.e[Q.rp].expireAt == currTime) {
		curr = dequeue();

		SCount[curr.y][curr.x]--;
		if (!SCount[curr.y][curr.x]) {
			Territory[curr.y][curr.x] = 0;
		}	
	}
}

void updateSmell(int currTime) {
	for (int id = 1; id <= NS; id++) {
		if (Sharks[id].isDead) {
			continue;
		}

		addSmell(newT[id].y, newT[id].x, id, currTime + SDuration);
	}

	removeSmell(currTime);
}

void input(void) {
	scanf("%d %d %d", &N, &NS, &SDuration);
	NAlive = NS;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%d", &Map[i][j]);
			if (Map[i][j] > 0) {
				addSmell(i, j, Map[i][j], SDuration);
				Sharks[Map[i][j]].y = i;
				Sharks[Map[i][j]].x = j;
			}
		}
	}

	for (int id = 1; id <= NS; id++) {
		scanf("%d", &Sharks[id].dir);
	}

	for (int id = 1; id <= NS; id++) {
		for (int d = 1; d <= 4; d++) {
			for (int i = 0; i < 4; i++) {
				scanf("%d", &Sharks[id].dPref[d][i]);
			}
		}
	}
}

int move1(int id) {
	int ny, nx, d;
	for (int i = 0; i < 4; i++) {
		d = Sharks[id].dPref[Sharks[id].dir][i];
		ny = Sharks[id].y + DIRS[d].dy;
		nx = Sharks[id].x + DIRS[d].dx;

		if (isOutOfBound(ny, nx) || Territory[ny][nx]) {
			continue;
		}

		if (Map[ny][nx]) {
			Map[Sharks[id].y][Sharks[id].x] = 0;
			Sharks[id].isDead = 1;
			NAlive--;
			return 1;
		}

		Map[ny][nx] = id;
		Map[Sharks[id].y][Sharks[id].x] = 0;
		Sharks[id].y = newT[id].y = ny;
		Sharks[id].x = newT[id].x = nx;
		Sharks[id].dir = d;
		return 1;
	}

	return 0;
}

int move2(int id) {
	int ny, nx, d;
	for (int i = 0; i < 4; i++) {
		d = Sharks[id].dPref[Sharks[id].dir][i];
		ny = Sharks[id].y + DIRS[d].dy;
		nx = Sharks[id].x + DIRS[d].dx;

		if (isOutOfBound(ny, nx) || Territory[ny][nx] != id) {
			continue;
		}

		Map[ny][nx] = id;
		Map[Sharks[id].y][Sharks[id].x] = 0;
		Sharks[id].y = newT[id].y = ny;
		Sharks[id].x = newT[id].x = nx;
		Sharks[id].dir = d;
		return 1;
	}

	return 0;
}

int progress(void) {
	for (int t = 1; t <= 1000; t++) {
		for (int id = 1; id <= NS; id++) {
			if (Sharks[id].isDead) {
				continue;
			}

			if (move1(id)) {
				continue;
			}

			move2(id);
		}

		updateSmell(t);

		if (NAlive == 1) {
			return t;
		}
	}

	return -1;
}

int main(void) {
	input();
	printf("%d", progress());

	return 0;
}