#include <stdio.h>

#define SP1 5
#define SP2 10
#define SP3 15
#define EXIT -1

typedef struct _Horse {
	int p;
	int idx;
} Horse;

const int PATHS[4][22] = {
	{ 0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, -1 },
	{ 10, 13, 16, 19, 25, 30, 35, 40, -1 },
	{ 20, 22, 24, 25, 30, 35, 40, -1 },
	{ 30, 28, 27, 26, 25, 30, 35, 40, -1 }
};

int commands[10];
int Max;

void input(void) {
	for (int i = 0; i < 10; i++) {
		scanf("%d", &commands[i]);
	}
}

Horse moveH(int c, Horse h) {
	if (h.p == 0 && (h.idx == SP1 || h.idx == SP2 || h.idx == SP3)) {
		h.p = h.idx / 5;
		h.idx = 0;
	}

	for (int i = 0; i < c; i++) {
		if (PATHS[h.p][h.idx] == EXIT) {
			break;
		}
		h.idx++;
	}
	
	return h;
}

int equals(Horse h1, Horse h2) {
	if (PATHS[h1.p][h1.idx] == EXIT || PATHS[h2.p][h2.idx] == EXIT) {
		return 0;
	}

	if (PATHS[h1.p][h1.idx] == 40 && PATHS[h2.p][h2.idx] == 40) {
		return 1;
	}

	if (PATHS[h1.p][h1.idx] == 25 && PATHS[h2.p][h2.idx] == 25) {
		return 1;
	}

	if (PATHS[h1.p][h1.idx] == 35 && PATHS[h2.p][h2.idx] == 35) {
		return 1;
	}

	if (PATHS[h1.p][h1.idx] == 30 && PATHS[h2.p][h2.idx] == 30 \
		&& (h1.p >= 1 && h1.p <= 3) && (h2.p >= 1 && h2.p <= 3)) {
		return 1;
	}

	return h1.idx == h2.idx && h1.p == h2.p;
}


void DFS(int depth, Horse h1, Horse h2, Horse h3, Horse h4, int score) {
	if (depth == 10) {
		if (score > Max) {
			Max = score;
		}
		return;
	}

	Horse temp;
	int gain;

	temp = moveH(commands[depth], h1);
	if (!equals(temp, h2) && !equals(temp, h3) && !equals(temp, h4)) {
		gain = (PATHS[temp.p][temp.idx] > 0) * PATHS[temp.p][temp.idx];
		DFS(depth + 1, temp, h2, h3, h4, score + gain);
	}

	temp = moveH(commands[depth], h2);
	if (!equals(temp, h1) && !equals(temp, h3) && !equals(temp, h4)) {
		gain = (PATHS[temp.p][temp.idx] > 0) * PATHS[temp.p][temp.idx];
		DFS(depth + 1, h1, temp, h3, h4, score + gain);
	}

	temp = moveH(commands[depth], h3);
	if (!equals(temp, h1) && !equals(temp, h2) && !equals(temp, h4)) {
		gain = (PATHS[temp.p][temp.idx] > 0) * PATHS[temp.p][temp.idx];
		DFS(depth + 1, h1, h2, temp, h4, score + gain);
	}

	temp = moveH(commands[depth], h4);
	if (!equals(temp, h1) && !equals(temp, h2) && !equals(temp, h3)) {
		gain = (PATHS[temp.p][temp.idx] > 0) * PATHS[temp.p][temp.idx];
		DFS(depth + 1, h1, h2, h3, temp, score + gain);
	}
}

int main(void) {
	input();
	Horse start = { 0, 0 };
	DFS(0, start, start, start, start, 0);
	printf("%d", Max);

	return 0;
}