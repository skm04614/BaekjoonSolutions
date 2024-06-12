#include <stdio.h>

typedef struct _Side {
	int val;
	int id;
	struct _Side *left;
	struct _Side *right;
	struct _Side *down;
	struct _Side *up;
} Side;

typedef struct _Direction {
	int dy;
	int dx;
} Direction;

const Direction DIRS[5] = { {0, 0}, {0, 1}, {0, -1}, {-1, 0}, {1, 0} };

Side Dice[6];
int Map[20][20];
int NRow, NCol;
int DY, DX;
int Commands[1000];
int NCom;
int Rot;

void input(void) {
	scanf("%d %d", &NRow, &NCol);
	scanf("%d %d", &DY, &DX);
	scanf("%d", &NCom);
	for (int i = 0; i < NRow; i++) {
		for (int j = 0; j < NCol; j++) {
			scanf("%d", &Map[i][j]);
		}
	}

	for (int i = 0; i < NCom; i++) {
		scanf("%d", &Commands[i]);
	}
}

void initDice(void) {
	Dice[0].left = &Dice[3];
	Dice[0].right = &Dice[2];
	Dice[0].down = &Dice[4];
	Dice[0].up = &Dice[1];

	Dice[1].left = &Dice[3];
	Dice[1].right = &Dice[2];
	Dice[1].down = &Dice[0];
	Dice[1].up = &Dice[5];

	Dice[2].left = &Dice[0];
	Dice[2].right = &Dice[5];
	Dice[2].down = &Dice[4];
	Dice[2].up = &Dice[1];

	Dice[3].left = &Dice[5];
	Dice[3].right = &Dice[0];
	Dice[3].down = &Dice[4];
	Dice[3].up = &Dice[1];

	Dice[4].left = &Dice[3];
	Dice[4].right = &Dice[2];
	Dice[4].down = &Dice[5];
	Dice[4].up = &Dice[0];

	Dice[5].left = &Dice[3];
	Dice[5].right = &Dice[2];
	Dice[5].down = &Dice[1];
	Dice[5].up = &Dice[4];

	Dice[0].id = 0;
	Dice[1].id = 1;
	Dice[2].id = 2;
	Dice[3].id = 3;
	Dice[4].id = 4;
	Dice[5].id = 5;
}

Side *rotate(Side *s, int dir) {
	Side *output = NULL;
	switch (dir) {
	case 1:
		if (Rot == 0) {
			output = s->left;
		}
		else if (Rot == 1) {
			output = s->down;
		}
		else if (Rot == 2) {
			output = s->right;
		} else {
			output = s->up;
		}
		break;
	case 2:
		if (Rot == 0) {
			output = s->right;
		}
		else if (Rot == 1) {
			output = s->up;
		}
		else if (Rot == 2) {
			output = s->left;
		}
		else {
			output = s->down;
		}
		break;
	case 3:
		if (Rot == 0) {
			output = s->down;
		}
		else if (Rot == 1) {
			output = s->right;
		}
		else if (Rot == 2) {
			output = s->up;
		}
		else {
			output = s->left;
		}
		break;
	case 4:
		if (Rot == 0) {
			output = s->up;
		}
		else if (Rot == 1) {
			output = s->left;
		}
		else if (Rot == 2) {
			output = s->down;
		}
		else {
			output = s->right;
		}
		break;
	}

	if (s->id == 1) {
		if (output->id == 2) {
			Rot = (Rot + 3) % 4;
		}
		if (output->id == 3) {
			Rot = (Rot + 1) % 4;
		}
	}

	if (s->id == 2) {
		if (output->id == 1) {
			Rot = (Rot + 1) % 4;
		}
		if (output->id == 4) {
			Rot = (Rot + 3) % 4;
		}
		if (output->id == 5) {
			Rot = (Rot + 2) % 4;
		}
	}

	if (s->id == 3) {
		if (output->id == 1) {
			Rot = (Rot + 3) % 4;
		}
		if (output->id == 4) {
			Rot = (Rot + 1) % 4;
		}
		if (output->id == 5) {
			Rot = (Rot + 2) % 4;
		}
	}

	if (s->id == 4) {
		if (output->id == 2) {
			Rot = (Rot + 1) % 4;
		}
		if (output->id == 3) {
			Rot = (Rot + 3) % 4;
		}
	}

	if (s->id == 5) {
		if (output->id == 2) {
			Rot = (Rot + 2) % 4;
		}
		if (output->id == 3) {
			Rot = (Rot + 2) % 4;
		}
	}

	return output;
}

int isOutOfBound(int y, int x) {
	return y < 0 || y >= NRow || x < 0 || x >= NCol;
}

void sol(void) {
	initDice();
	Side *up = &Dice[0];

	int d;
	for (int i = 0; i < NCom; i++) {
		d = Commands[i];
		DY += DIRS[d].dy;
		DX += DIRS[d].dx;

		if (isOutOfBound(DY, DX)) {
			DY -= DIRS[d].dy;
			DX -= DIRS[d].dx;
			continue;
		}

		up = rotate(up, d);
		printf("%d\n", up->val);
		if (Map[DY][DX] == 0) {
			Map[DY][DX] = Dice[5 - up->id].val;
		}
		else {
			Dice[5 - up->id].val = Map[DY][DX];
			Map[DY][DX] = 0;
		}
	}
}

int main(void) {
	input();
	sol();

	return 0;
}