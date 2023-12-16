#include <bits/stdc++.h>
using namespace std;

enum {
	DASH,
	PIPE,
	SLASH,
	BACKSLASH,
	EMPTY
};

#define DIR2IND(x) (x + 1)
#define DIRS2IND(y, x) ((DIR2IND(y) << 2) | DIR2IND(x))

void dfs(vector<vector<int>>& grid, vector<vector<array<bool, 16>>>& vis, int y, int x, int dy, int dx) {
	if (y < 0 || x < 0 || y >= (int)grid.size() || x >= (int)grid[0].size()) return;
	if (vis[y][x][DIRS2IND(dy, dx)]) return;
	vis[y][x][DIRS2IND(dy, dx)] = true;

	if (grid[y][x] == PIPE && dx) {
		dfs(grid, vis, y + 1, x, 1, 0);
		dfs(grid, vis, y - 1, x, -1, 0);
	} else if (grid[y][x] == DASH && dy) {
		dfs(grid, vis, y, x + 1, 0, 1);
		dfs(grid, vis, y, x - 1, 0, -1);
	} else if (grid[y][x] == SLASH) {
		if (dy == 1) {
			dfs(grid, vis, y, x - 1, 0, -1);
		} else if (dy == -1) {
			dfs(grid, vis, y, x + 1, 0, 1);
		} else if (dx == 1) {
			dfs(grid, vis, y - 1, x, -1, 0);
		} else if (dx == -1) {
			dfs(grid, vis, y + 1, x, 1, 0);
		} else {
			assert(false);
		}
	} else if (grid[y][x] == BACKSLASH) {
		if (dy == 1) {
			dfs(grid, vis, y, x + 1, 0, 1);
		} else if (dy == -1) {
			dfs(grid, vis, y, x - 1, 0, -1);
		} else if (dx == 1) {
			dfs(grid, vis, y + 1, x, 1, 0);
		} else if (dx == -1) {
			dfs(grid, vis, y - 1, x, -1, 0);
		} else {
			assert(false);
		}
	} else {
		dfs(grid, vis, y + dy, x + dx, dy, dx);
	}
}

int calc_coverage(vector<vector<int>>& grid, int y, int x, int dy, int dx) {
	vector<vector<array<bool, 16>>> vis(grid.size(), vector<array<bool, 16>>(grid[0].size()));
	dfs(grid, vis, y, x, dy, dx);

	int tot = 0;
	for (size_t y = 0; y < grid.size(); y++) {
		for (size_t x = 0; x < grid[0].size(); x++) {
			for (size_t i = 0; i < 16; i++) {
				if (vis[y][x][i]) {
					tot++;
					break;
				}
			}
		}
	}
	return tot;
}

int main ()
{
	vector<vector<int>> grid;
	string line;

	while (cin >> line) {
		vector<int> row;
		row.reserve(line.size());
		for (char c : line) {
			if (c == '/') {
				row.push_back(SLASH);
			} else if (c == '\\') {
				row.push_back(BACKSLASH);
			} else if (c == '-') {
				row.push_back(DASH);
			} else if (c == '|') {
				row.push_back(PIPE);
			} else {
				row.push_back(EMPTY);
			}
		}
		grid.push_back(std::move(row));
	}

	int nax = 0;
	for (size_t x = 0; x < grid[0].size(); x++) {
		int act = calc_coverage(grid, 0, x, 1, 0);
		nax = max(nax, act);
	}
	for (size_t y = 0; y < grid.size(); y++) {
		int act = calc_coverage(grid, y, 0, 0, 1);
		nax = max(nax, act);
	}
	for (size_t x = 0; x < grid[0].size(); x++) {
		int act = calc_coverage(grid, grid.size() - 1, x, -1, 0);
		nax = max(nax, act);
	}
	for (size_t y = 0; y < grid.size(); y++) {
		int act = calc_coverage(grid, y, grid[0].size() - 1, 0, -1);
		nax = max(nax, act);
	}

	cout << nax << endl;
}
