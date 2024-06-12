#include <iostream>

#define SIZE 1000000

int Arr[SIZE];
int Temp[SIZE];
int N;

using namespace std;

void input(void) {
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> Arr[i];
	}
}

void merge(int, int);

void sort(int lower, int upper) {
	if (lower >= upper) {
		return;
	}

	int mid = (lower + upper) / 2;
	sort(lower, mid);
	sort(mid + 1, upper);
	merge(lower, upper);
}

void merge(int lower, int upper) {
	int mid = (lower + upper) / 2;
	int l = lower;
	int r = mid + 1;
	int idx = lower;

	while (l <= mid && r <= upper) {
		if (Arr[l] <= Arr[r]) {
			Temp[idx++] = Arr[l++];
		}
		else {
			Temp[idx++] = Arr[r++];
		}
	}

	while (l <= mid) {
		Temp[idx++] = Arr[l++];
	}

	while (r <= upper) {
		Temp[idx++] = Arr[r++];
	}

	for (int i = lower; i <= upper; i++) {
		Arr[i] = Temp[i];
	}
}

void display(void) {
	for (int i = 0; i < N; i++) {
		cout << Arr[i] << endl;
	}
}

int main(void) {
	input();
	sort(0, N - 1);
	display();

	return 0;
}