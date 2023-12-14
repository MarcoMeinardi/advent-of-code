#include <bits/stdc++.h>
using namespace std;

int main ()
{
	vector<string> grid;
	string line;

	while (cin >> line) {
		grid.push_back(std::move(line));
	}

	size_t n = grid.size();
	size_t m = grid[0].size();
	uint64_t tot = 0;

	for (size_t x = 0; x < m; x++) {
		size_t y_off = 0;
		for (size_t y = 0; y < n; y++) {
			if (grid[y][x] == 'O') {
				tot += n - y_off++;
			} else if (grid[y][x] == '#') {
				y_off = y + 1;
			}
		}
	}

	cout << tot << endl;
}
