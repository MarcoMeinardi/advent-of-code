#include <bits/stdc++.h>
using namespace std;

int main () {
	int score = 0;
	char you, me;
	int iyou, ime;
	int map[0x100] = {};
	map['X'] = 0;
	map['Y'] = 1;
	map['Z'] = 2;
	map['A'] = 0;
	map['B'] = 1;
	map['C'] = 2;

	while (cin >> you >> me) {
		iyou = map[(int)you];
		ime = map[(int)me];
		score += ime + 1;
		if (ime == iyou) {
			score += 3;
		} else if ((iyou + 1) % 3 == ime) {
			score += 6;
		}
	}
	cout << score << endl;
}
