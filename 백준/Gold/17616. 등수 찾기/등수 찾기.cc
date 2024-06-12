#include <cstdio>

#define NULL			 0
#define MAX_NODE	100010
#define MAX_EDGE	500050
#define ORIGINAL		 0
#define REVERSED		 1

struct Edge {
	int tgt;
	Edge *next;
	Edge *alloc(int tgt, Edge *next) {
		this->tgt = tgt;
		this->next = next;
		return this;
	}
} EPool[2 * MAX_EDGE];
Edge *Record[2][MAX_NODE];
bool VC[MAX_NODE];
int N, E, Target;

struct Queue {
	int data[MAX_NODE];
	int wp, rp;

	void init(void) {
		wp = rp = 0;
	}

	bool isEmpty(void) {
		return rp >= wp;
	}

	void enqueue(int n) {
		data[wp++] = n;
	}

	int dequeue(void) {
		return data[rp++];
	}
} Q;

void init(void) {
	for (register int i = 0; i <= N; i++) Record[0][i] = Record[1][i] = NULL;
	for (register int i = 0; i <= N; i++) VC[i] = false;
	Q.init();
}

void input(void) {
	scanf("%d %d %d", &N, &E, &Target);
	register Edge *edge;
	for (register int s, t, i = 0; i < 2 * E; i += 2) {
		scanf("%d %d", &s, &t);
		edge = EPool[i].alloc(t, Record[ORIGINAL][s]);
		Record[ORIGINAL][s] = edge;
		edge = EPool[i + 1].alloc(s, Record[REVERSED][t]);
		Record[REVERSED][t] = edge;
	}
}

void sol(void) {
	register int lower = N;
	Q.enqueue(Target);
	while (!Q.isEmpty()) {
		register int temp = Q.dequeue();
		for (register Edge *edge = Record[ORIGINAL][temp]; edge; edge = edge->next) {
			if (VC[edge->tgt]) continue;
			VC[edge->tgt] = true;
			Q.enqueue(edge->tgt);
			lower--;
		}
	}

	register int upper = 1;
	Q.enqueue(Target);
	while (!Q.isEmpty()) {
		register int temp = Q.dequeue();
		for (register Edge *edge = Record[REVERSED][temp]; edge; edge = edge->next) {
			if (VC[edge->tgt]) continue;
			VC[edge->tgt] = true;
			Q.enqueue(edge->tgt);
			upper++;
		}
	}
	printf("%d %d", upper, lower);
}


int main(void) {
	init();
	input();
	sol();
	return 0;
}