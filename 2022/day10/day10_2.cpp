#include <bits/stdc++.h>
using namespace std;

int main () {
	int X = 1;
	int cycle = 0;

	vector <string> table(6, string(40, ' '));
	string instr;
	int op;

	while (cin >> instr) {
		int pos = cycle % 40;
		if (pos == X - 1 || pos == X || pos == X + 1) {
			table[cycle / 40][pos] = '#';
		}
		cycle++;
		if (instr == "addx") {
			cin >> op;
			pos = cycle % 40;
			if (pos == X - 1 || pos == X || pos == X + 1) {
				table[cycle / 40][pos] = '#';
			}
			cycle++;
			X += op;
		}
	}

	for (string& s : table) {
		cout << s << endl;
	}
}
