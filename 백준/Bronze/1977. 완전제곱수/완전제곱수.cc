#include <iostream>

int Sq[101];

using namespace std;

void init(void) {
	for (int i = 1; i <= 100; i++) {
		Sq[i] = i * i;
	}
}

void sol(void) {
	int m, n;
	cin >> m >> n;

	int min = 0;
	int sum = 0;
	for (int i = 1; i <= 100; i++) {
		if (m > Sq[i]) continue;
		if (n < Sq[i]) break;
		if (!min) min = Sq[i];
		sum += Sq[i];
	}

	if (sum) {
		cout << sum << endl;
		cout << min << endl;
	}
	else {
		cout << -1;
	}
}

int main(void) {
	init();
	sol();

	return 0;
}