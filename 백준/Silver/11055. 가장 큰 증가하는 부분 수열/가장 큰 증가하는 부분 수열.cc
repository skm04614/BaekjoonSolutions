#include <iostream>

using namespace std;

int N;
int Arr[1001];
int Sum[1001];

int sol(void) {
	Sum[0] = 0;

	int max = 0;
	for (int i = 1; i <= N; i++) {
		int temp = 0;
		for (int j = i - 1; j >= 0; j--) {
			temp = (Arr[i] > Arr[j] && temp < Sum[j]) ? Sum[j] : temp;
		}
		Sum[i] = temp + Arr[i];
		max = max > Sum[i] ? max : Sum[i];
	}

	return max;
}

int main(void) {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Arr[i];
	}
	cout << sol();

	return 0;
}