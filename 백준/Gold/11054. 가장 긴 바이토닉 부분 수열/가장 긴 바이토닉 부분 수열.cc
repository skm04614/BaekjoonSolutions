#include <iostream>

using namespace std;

int Arr[1002];
int Record[2][1002];
int N;

int sol(void) {
	Arr[0] = Arr[N + 1] = 0;
	Record[0][0] = Record[1][0] = 0;

	for (int i = 1; i <= N; i++) {
		int temp = 0;
		int temp2 = 0;
		for (int j = i - 1; j >= 0; j--) {
			if (Arr[i] > Arr[j]) {
				temp = temp > Record[0][j] ? temp : Record[0][j];
			}

			if (Arr[N + 1 - i] > Arr[N + 1 - j]) {
				temp2 = temp2 > Record[1][N + 1 - j] ? temp2 : Record[1][N + 1 - j];
			}
		}
		Record[0][i] = temp + 1;
		Record[1][N + 1 - i] = temp2 + 1;
	}

	int result = 0;
	for (int i = 1; i <= N; i++) {
		int temp = Record[0][i] + Record[1][i] - 1;
		result = result > temp ? result : temp;
	}

	return result;
}

int main(void) {
	cin >> N;
	for (int i = 1; i <= N; i++) {
		cin >> Arr[i];
	}
	
	cout << sol();

	return 0;
}