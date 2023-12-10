#include <bits/stdc++.h>
using namespace std;

#define UP 0b0001
#define RIGHT 0b0010
#define DOWN 0b0100
#define LEFT 0b1000

const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, 1, 0, -1};

int char2pipe[0x80];
__attribute__((constructor)) void init_char2pipe()
{
	char2pipe['S'] = UP | RIGHT | DOWN | LEFT;
	char2pipe['|'] = UP | DOWN;
	char2pipe['-'] = LEFT | RIGHT;
	char2pipe['L'] = UP | RIGHT;
	char2pipe['J'] = UP | LEFT;
	char2pipe['7'] = DOWN | LEFT;
	char2pipe['F'] = DOWN | RIGHT;
	char2pipe['.'] = 0;
};

void dfs(int y, int x, vector<vector<int>>& grid, vector<vector<int>>& dist, int depth=0)
{
	if (dist[y][x] != -1 && dist[y][x] <= depth) return;
	dist[y][x] = depth;
	for (int i = 0; i < 4; i++) {
		if (!(grid[y][x] & (1 << i))) continue;
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (ny < 0 || ny >= (int)grid.size() || nx < 0 || nx >= (int)grid[0].size()) continue;
		if (!(grid[ny][nx] & (1 << ((i + 2) & 3)))) continue;
		dfs(ny, nx, grid, dist, depth + 1);
	}
}

int main ()
{
	vector<vector<int>> grid;
	string line;

	int sy = -1, sx = -1;
	while (cin >> line) {
		grid.push_back(vector<int>(line.size()));
		for (size_t i = 0; i < line.size(); i++) {
			grid.back()[i] = char2pipe[(int)line[i]];
			if (line[i] == 'S') {
				sy = grid.size() - 1;
				sx = i;
			}
		}
	}
	assert(sy != -1 && sx != -1);
	vector<vector<int>> dist(grid.size(), vector<int>(grid[0].size(), -1));
	dfs(sy, sx, grid, dist);

	int ans = 0;
	for (vector<int>& v : dist) {
		for (int i : v) {
			ans = max(ans, i);
		}
	}

	cout << ans << endl;
}
