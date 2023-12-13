#include <bits/stdc++.h>
using namespace std;


uint64_t solve(vector<string>& rows)
{
	vector<string> cols(rows[0].size());
	for (size_t x = 0; x < cols.size(); x++) {
		for (size_t y = 0; y < rows.size(); y++) {
			cols[x] += rows[y][x];
		}
	}

	for (size_t y_split = 0; y_split < rows.size() - 1; y_split++) {
		bool ok = true;
		for (int above = y_split, below = y_split + 1; above >= 0 && below < (int)rows.size(); above--, below++) {
			if (rows[above] != rows[below]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			return (y_split + 1) * 100ULL;
		}
	}

	for (size_t x_split = 0; x_split < cols.size() - 1; x_split++) {
		bool ok = true;
		for (int left = x_split, right = x_split + 1; left >= 0 && right < (int)cols.size(); left--, right++) {
			if (cols[left] != cols[right]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			return (x_split + 1);
		}
	}

	assert(false);
}

int main ()
{
	string line;
	vector<string> grid;
	uint64_t tot = 0;

	while (getline(cin, line)) {
		if (line.empty()) {
			tot += solve(grid);
			grid.clear();
		} else {
			grid.push_back(line);
		}
	}
	tot += solve(grid);

	cout << tot << endl;
}
