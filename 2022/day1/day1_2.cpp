#include <bits/stdc++.h>
using namespace std;

int main () {
	vector <int> elves;
	string line;

	while (true) {
		int elf = 0;
		while (true) {
			if (!getline(cin, line)) goto done;
			if (line.empty()) break;
			elf += stoi(line);
		}
		elves.push_back(elf);
	}
done:
	partial_sort(elves.begin(), elves.begin() + 3, elves.end(), greater());
	cout << (elves[0] + elves[1] + elves[2]) << endl;

	return 0;
}
