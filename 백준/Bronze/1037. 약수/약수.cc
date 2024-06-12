#include <iostream>
using namespace std;

#define SWAP(n1, n2) {int temp = (n1); (n1) = (n2); (n2) = temp;}

void bubbleSort(int *p, int size) {
	for (int i = 1; i < size; i++) {
		for (int j = 0; j < size - i; j++) {
			if (p[j] > p[j + 1]) {
				SWAP(p[j], p[j + 1]);
			}
		}
	}
}

int main(void) {
	int div[50];
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> div[i];
	}
	bubbleSort(div, n);

	if (n == 1) {
		cout << div[0] * div[0];
	}
	else {
		cout << div[0] * div[n - 1];
	}

	return 0;
}