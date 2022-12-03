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

	string line;
	int tot = 0;
	while (cin >> line) {
		bool appears[0x80] = {};
		for (size_t i = 0; i < line.size() / 2; i++) {
			appears[(size_t)line[i]] = true;
		}
		for (size_t i = line.size() / 2; i < line.size(); i++) {
			if (appears[(size_t)line[i]]) {
				tot += priorities[(size_t)line[i]];
				break;
			}
		}
	}

	cout << tot << endl;
}
