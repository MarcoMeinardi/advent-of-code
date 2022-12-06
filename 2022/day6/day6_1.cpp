#include <bits/stdc++.h>
using namespace std;

int main () {
	string line;

	cin >> line;
	vector <char> window(4);
	for (size_t i = 0; i < line.size(); i++) {
		window[i % 4] = line[i];
		if (i >= 3) {
			bool ok = true;
			for (size_t a = 0; a < 3; a++) {
				for (size_t b = a + 1; b < 4; b++) {
					if (window[a] == window[b]) {
						ok = false;
					}
				}
			}
			if (ok) {
				cout << (i + 1) << endl;
				break;
			}
		}
	}
}
