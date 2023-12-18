#include <bits/stdc++.h>
using namespace std;

#define IN 1
#define OUT 2

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int char2dir[0x80];

__attribute__((constructor)) void init_char2dir()
{
	char2dir['U'] = 0;
	char2dir['R'] = 1;
	char2dir['D'] = 2;
	char2dir['L'] = 3;
}

void step(deque<deque<int>>& grid, int& y, int& x, int dir)
{
	int ny = y + dy[dir];
	int nx = x + dx[dir];

	if (ny < 0) {
		grid.push_front(deque<int>(grid[0].size(), 0));
		ny = 0;
	}
	if (nx < 0) {
		for (deque<int>& row : grid) {
			row.push_front(0);
		}
		nx = 0;
	}
	if (ny >= (int)grid.size()) {
		grid.push_back(deque<int>(grid[0].size(), 0));
	}
	if (nx >= (int)grid[0].size()) {
		for (deque<int>& row : grid) {
			row.push_back(0);
		}
	}
	grid[ny][nx] = IN;

	y = ny;
	x = nx;
}

void fill_inout(vector<vector<int>>& grid, int y, int x, int val)
{
	if (y < 0 || x < 0 || y >= (int)grid.size() || x >= (int)grid[0].size()) return;
	if (grid[y][x]) return;

	grid[y][x] = val;
	for (int i = 0; i < 4; i++) {
		fill_inout(grid, y + dy[i], x + dx[i], val);
	}
}

int main ()
{
	deque<deque<int>> grid;
	char dir_c;
	int dir;
	int steps;
	string color_str;
	__attribute__((unused)) uint32_t color;

	int y = 0, x = 0;
	grid.push_back(deque<int>(1, true));

	while (cin >> dir_c >> steps >> color_str) {
		dir = char2dir[(int)dir_c];
		color = stoull(color_str.substr(2, 6), nullptr, 16);

		while (steps--) {
			step(grid, y, x, dir);
		}
	}

	for (deque<int>& row : grid) {
		row.push_front(0);
		row.push_back(0);
	}
	grid.push_front(deque<int>(grid[0].size(), 0));
	grid.push_back(deque<int>(grid[0].size(), 0));

	vector<vector<int>> vgrid(grid.size(), vector<int>(grid[0].size()));
	for (size_t i = 0; i < grid.size(); i++) {
		for (size_t j = 0; j < grid[i].size(); j++) {
			vgrid[i][j] = grid[i][j];
		}
	}

	fill_inout(vgrid, 0, 0, OUT);
	for (size_t y = 0; y < vgrid.size(); y++) {
		for (size_t x = 0; x < vgrid[y].size(); x++) {
			if (!vgrid[y][x]) {
				fill_inout(vgrid, y, x, IN);
				goto done_fill;
			}
		}
	}
	done_fill:;

	int tot = 0;
	for (size_t i = 0; i < vgrid.size(); i++) {
		for (size_t j = 0; j < vgrid[i].size(); j++) {
			tot += vgrid[i][j] == IN;
		}
	}

	cout << tot << endl;
}
