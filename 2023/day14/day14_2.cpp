#include <bits/stdc++.h>
using namespace std;


string grid2str(vector<string>& grid)
{
	string s;
	for (auto& line : grid) {
		s += line;
	}
	return s;
}

const int dy[] = {1, 0, -1 ,0};
const int dx[] = {0, 1, 0, -1};

void spin(vector<string>& grid, int n, int m)
{
	int start[] = {0, 0, n - 1, m - 1};
	for (int i = 0; i < 4; i++) {
		if (i & 1) {  // horizontal
			for (int y = 0; y < m; y++) {
				int x_off = start[i];
				for (int x = start[i]; x >= 0 && x < m; x += dx[i]) {
					if (grid[y][x] == 'O') {
						grid[y][x] = '.';
						grid[y][x_off] = 'O';
						x_off += dx[i];
					} else if (grid[y][x] == '#') {
						x_off = x + dx[i];
					}
				}
			}
		} else {  // vertical
			for (int x = 0; x < m; x++) {
				int y_off = start[i];
				for (int y = start[i]; y >= 0 && y < n; y += dy[i]) {
					if (grid[y][x] == 'O') {
						grid[y][x] = '.';
						grid[y_off][x] = 'O';
						y_off += dy[i];
					} else if (grid[y][x] == '#') {
						y_off = y + dy[i];
					}
				}
			}
		}
	}
}

int get_weight(vector<string>& grid, int n, int m)
{
	int weight = 0;
	for (int y = 0; y < n; y++) {
		for (int x = 0; x < m; x++) {
			if (grid[y][x] == 'O') {
				weight += n - y;
			}
		}
	}
	return weight;
}

int main ()
{
	vector<string> grid;
	string line;

	while (cin >> line) {
		grid.push_back(std::move(line));
	}

	int n = (int)grid.size();
	int m = (int)grid[0].size();

	unordered_map<string, int> seen;
	vector<vector<string>> prev_list;

	string s;
	int cycle_len, cycle_start;
	int ind = 0;

	while (true) {
		s = grid2str(grid);
		seen[s] = ind;
		prev_list.push_back(grid);
		spin(grid, n, m);
		ind++;

		s = grid2str(grid);
		auto it = seen.find(s);
		if (it != seen.end()) {
			cycle_len = ind - it->second;
			cycle_start = it->second;
			break;
		}
	}

	int final_grid_ind = (1000000000 - cycle_start) % cycle_len + cycle_start;
	vector<string>& final_grid = prev_list[final_grid_ind];

	cout << get_weight(final_grid, n, m) << endl;
}
