#include <bits/stdc++.h>
using namespace std;

int main () {
	int score = 0;
	char you, me;
	int iyou;
	int map[0x100] = {};
	map['A'] = 0;
	map['B'] = 1;
	map['C'] = 2;

	while (cin >> you >> me) {
		iyou = map[(int)you];
		if (me == 'X') {
			score += (iyou + 2) % 3 + 1;
		} else if (me == 'Y') {
			score += iyou + 1 + 3;
		} else {
			score += (iyou + 1) % 3 + 1 + 6;
		}
	}
	cout << score << endl;
}
