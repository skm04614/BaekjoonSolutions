#include <iostream>

using namespace std;

int Arr[1001];
int N;
int Seq[1001];

int sol(void) {
	int L = 0;
	Seq[L] = 0x7FFFFFFF;

	for (int i = 1; i <= N; i++) {
		int flag = 1;
		for (int j = 0; j <= L; j++) {
			if (Arr[i] >= Seq[j]) {
				Seq[j] = Arr[i];
				flag = 0;
				break;
			}
		}
		if (flag) {
			Seq[++L] = Arr[i];
		}
	}

	return L;
}

int main(void) {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Arr[i];
	}

	cout << sol();

	return 0;
}