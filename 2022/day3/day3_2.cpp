#include <bits/stdc++.h>
using namespace std;

int main () {
	int priorities[0x80] = {};
	for (int i = 'a', j = 1; i <= 'z'; i++, j++) {
		priorities[i] = j;
	}
	for (int i = 'A', j = 27; i <= 'Z'; i++, j++) {
		priorities[i] = j;
	}

	string elves[3];
	int tot = 0;
	while (cin >> elves[0] >> elves[1] >> elves[2]) {
		bool appears[3][0x80] = {};
		for (int i = 0; i < 3; i++) {
			for (char c : elves[i]) {
				appears[i][(size_t)c] = true;
			}
		}

		for (size_t i = 0; i < 0x80; i++) {
			if (appears[0][i] && appears[1][i] && appears[2][i]) {
				tot += priorities[i];
				break;
			}
		}
	}

	cout << tot << endl;
}
