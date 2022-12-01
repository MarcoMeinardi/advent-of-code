#include <bits/stdc++.h>
using namespace std;

int main () {
	int nax = 0;
	string line;

	while (true) {
		int elf = 0;
		while (true) {
			if (!getline(cin, line)) goto done;
			if (line.empty()) break;
			elf += stoi(line);
		}
		nax = max(nax, elf);
	}
done:
	cout << nax << endl;

	return 0;
}
