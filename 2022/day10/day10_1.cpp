#include <bits/stdc++.h>
using namespace std;

int main () {
	int X = 1;
	int cycle = 0;

	string instr;
	int op;
	int tot = 0;

	while (cin >> instr) {
		cycle++;
		if ((cycle - 20) % 40 == 0) {
			tot += cycle * X;
		}
		if (instr == "addx") {
			cin >> op;
			cycle++;
			if ((cycle - 20) % 40 == 0) {
				tot += cycle * X;
			}
			X += op;
		}
	}

	cout << tot << endl;
}
