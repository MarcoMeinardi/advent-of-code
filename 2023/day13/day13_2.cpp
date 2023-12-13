#include <bits/stdc++.h>
using namespace std;

pair<bool, bool> my_strcmp(const string& a, const string& b)
{
	bool eq = true;
	bool smudge = false;
	for (size_t i = 0; i < a.size(); i++) {
		if (a[i] != b[i]) {
			if (smudge) {
				return {false, false};
			}
			smudge = true;
		}
	}
	return {eq, smudge};
}

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
		bool smudged = false;
		for (int above = y_split, below = y_split + 1; above >= 0 && below < (int)rows.size(); above--, below++) {
			auto [eq, with_smudge] = my_strcmp(rows[above], rows[below]);
			if (!eq || (with_smudge && smudged)) {
				ok = false;
				break;
			}
			if (with_smudge) {
				smudged = true;
			}
		}
		if (ok && smudged) {
			return (y_split + 1) * 100ULL;
		}
	}

	for (size_t x_split = 0; x_split < cols.size() - 1; x_split++) {
		bool ok = true;
		bool smudged = false;
		for (int left = x_split, right = x_split + 1; left >= 0 && right < (int)cols.size(); left--, right++) {
			auto [eq, with_smudge] = my_strcmp(cols[left], cols[right]);
			if (!eq || (with_smudge && smudged)) {
				ok = false;
				break;
			}
			if (with_smudge) {
				smudged = true;
			}
		}
		if (ok && smudged) {
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
