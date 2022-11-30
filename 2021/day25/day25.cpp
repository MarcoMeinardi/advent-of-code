#include <bits/stdc++.h>
using namespace std;


bool step(uint8_t grid[1000][1000], uint8_t cp[1000][1000], int n, int m) {
	bool change = false;
	memset(cp, 0, 1000 * 1000);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 1 && grid[i][(j + 1) % m] == 0) {
				cp[i][(j + 1) % m] = 1;
				cp[i][j] = 0;
				change = true;
			} else if (grid[i][j] != 0) {
				cp[i][j] = grid[i][j];
			}
		}
	}
	memcpy(grid, cp, 1000 * 1000);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 2 && grid[(i + 1) % n][j] == 0) {
				cp[(i + 1) % n][j] = 2;
				cp[i][j] = 0;
				change = true;
			} else if (grid[i][j] != 0) {
				cp[i][j] = grid[i][j];
			}
		}
	}
	memcpy(grid, cp, 1000 * 1000);

	return change;
}

int main () {
	uint8_t grid[1000][1000] = {};
	uint8_t cp[1000][1000];
	uint8_t conv[0x80] = {};
	int n, m;
	string line;
	int tot = 1;

	conv['.'] = 0;
	conv['>'] = 1;
	conv['v'] = 2;

	n = 0;
	while(cin >> line) {
		for (m = 0; m < (int)line.size(); m++) {
			grid[n][m] = conv[(int)line[m]];
		}
		n++;
	}

	while(step(grid, cp, n, m)) {
		tot++;
	}

	cout << tot << endl;
	return 0;
}