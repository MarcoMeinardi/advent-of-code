#include <bits/stdc++.h>
using namespace std;

int main () {
	string line;
	vector <string> grid;
	vector <vector <bool>> visible;

	while (cin >> line) {
		grid.push_back(line);
	}

	int n = (int)grid.size(), m = (int)grid[0].size();
	visible.resize(n, vector <bool> (m, false));

	for (int i = 0; i < n; i++) {
		char max_h = '\0';
		for (int j = 0; j < m; j++) {
			if (grid[i][j] > max_h) {
				visible[i][j] = true;		
				max_h = grid[i][j];
			}
		}
		max_h = '\0';
		for (int j = m - 1; j >= 0; j--) {
			if (grid[i][j] > max_h) {
				visible[i][j] = true;		
				max_h = grid[i][j];
			}
		}
	}

	for (int j = 0; j < m; j++) {
		char max_h = '\0';
		for (int i = 0; i < n; i++) {
			if (grid[i][j] > max_h) {
				visible[i][j] = true;		
				max_h = grid[i][j];
			}
		}
		max_h = '\0';
		for (int i = n - 1; i >= 0; i--) {
			if (grid[i][j] > max_h) {
				visible[i][j] = true;		
				max_h = grid[i][j];
			}
		}
	}

	int tot = accumulate(visible.begin(), visible.end(), 0,
		[] (int res, vector <bool>& row) { return res + accumulate(row.begin(), row.end(), 0); });

	cout << tot << endl;

}
