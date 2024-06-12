#include <stdio.h>

#define N		0
#define S		1
#define RIGHT	2
#define LEFT	6

typedef struct _Action {
	int g;
	int dir;
} Action;

Action Actions[100];
int NAct;
int Gears[4][8];

void rotate(int *p, int size, int dir) {
	int temp;
	if (dir == 1) {
		temp = p[size - 1];
		for (int i = size - 1; i > 0; i--) {
			p[i] = p[i - 1];
		}
		p[0] = temp;
	}
	else if (dir == -1) {
		temp = p[0];
		for (int i = 0; i < size - 1; i++) {
			p[i] = p[i + 1];
		}
		p[size - 1] = temp;
	}
}

void move(int g, int dir) {
	int doesRot[4] = { 0 };
	doesRot[g] = dir;
	int r = g + 1;
	int dr = dir;
	while (r < 4) {
		dr *= -1 * (Gears[r - 1][RIGHT] ^ Gears[r][LEFT]);
		if (!dr) {
			break;
		}
		doesRot[r] = dr;
		r++;
	}

	int l = g - 1;
	int dl = dir;
	while (l >= 0) {
		dl *= -1 * (Gears[l + 1][LEFT] ^ Gears[l][RIGHT]);
		if (!dl) {
			break;
		}
		doesRot[l] = dl;
		l--;
	}

	for (int i = 0; i < 4; i++) {
		rotate(Gears[i], 8, doesRot[i]);
	}
}

int getScore(void) {
	return (Gears[0][0] == S) + 2 * (Gears[1][0] == S) \
		+ 4 * (Gears[2][0] == S) + 8 * (Gears[3][0] == S);
}

void input(void) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 8; j++) {
			scanf("%1d", &Gears[i][j]);
		}
	}
	scanf("%d", &NAct);
	for (int i = 0; i < NAct; i++) {
		scanf("%d %d", &Actions[i].g, &Actions[i].dir);
	}
}

int main(void) {
	input();
	for (int i = 0; i < NAct; i++) {
		move(Actions[i].g - 1, Actions[i].dir);
	}

	printf("%d", getScore());

	return 0;
}