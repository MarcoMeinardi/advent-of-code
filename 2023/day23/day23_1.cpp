#include <bits/stdc++.h>
using namespace std;

#define EMPTY 4
#define WALL 5
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};

int char2int[0x80];
__attribute__((constructor)) void init()
{
	char2int['.'] = EMPTY;
	char2int['#'] = WALL;
	char2int['^'] = 0;
	char2int['>'] = 1;
	char2int['v'] = 2;
	char2int['<'] = 3;
}

int dfs(vector<vector<int>>& grid, int y, int x, vector<vector<bool>>& vis, int depth=0)
{
	if (y == (int)grid.size() - 1) {
		return depth;
	}
	if (vis[y][x]) return 0;
	vis[y][x] = true;

	int res = 0;
	for (int i = 0; i < 4; i++) {
		int ny = y + dy[i];
		int nx = x + dx[i];
		if (grid[ny][nx] == EMPTY) {
			int act = dfs(grid, ny, nx, vis, depth + 1);
			res = max(act, res);
		} else if (grid[ny][nx] == i) {
			int act = dfs(grid, ny + dy[i], nx + dx[i], vis, depth + 2);
			res = max(act, res);
		}
	}
	vis[y][x] = false;
	return res;
}

int main ()
{
	string line;
	vector<vector<int>> grid;

	while (cin >> line) {
		vector<int> row;
		if (grid.empty()) grid.push_back(vector<int>(line.size(), WALL));
		row.reserve(line.size());
		for (char c : line) {
			row.push_back(char2int[(int)c]);
		}
		grid.push_back(std::move(row));
	}

	vector<vector<bool>> vis(grid.size(), vector<bool>(grid[0].size(), false));
	int ans = dfs(grid, 1, 1, vis);

	cout << ans << endl;
}
