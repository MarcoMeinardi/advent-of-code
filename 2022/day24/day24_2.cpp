#include <bits/stdc++.h>
using namespace std;

int n, m;
const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

vector<string> grid;
struct blizzard_t {
	int y;
	int x;
	int dir;

	blizzard_t(int y, int x, int dir): y(y - 1), x(x - 1), dir(dir) {}

	void move() {
		y = (y + dy[dir] + (n - 2)) % (n - 2);
		x = (x + dx[dir] + (m - 2)) % (m - 2);
	}
};
vector<blizzard_t> blizzards;

void draw_blizzards() {
	for (int y = 1; y < n - 1; y++) {
		for (int x = 1; x < m - 1; x++) {
			grid[y][x] = '.';
		}
	}
	for (blizzard_t& blizzard : blizzards) {
		blizzard.move();
		grid[blizzard.y + 1][blizzard.x + 1] = '@';
	}
}

int bfs(int start_y, int start_x, int end_y, int end_x) {
	queue<tuple<int, int, int>> q;  // y, x, t
	q.emplace(start_y, start_x, 0);
	vector<vector<bool>> vis;

	int p_time = -1;
	while (!q.empty()) {
		auto [y, x, t] = q.front();
		q.pop();
		if (t != p_time) {
			assert(t == p_time + 1);
			p_time++;
			draw_blizzards();
			vis.assign(n, vector<bool>(m));
		}
		if (y == end_y) {
			assert(x == end_x);
			return t;
		}

		if (!vis[y][x] && grid[y][x] == '.') q.emplace(y, x, t + 1);
		vis[y][x] = true;

		for (int i = 0; i < 4; i++) {
			int ny = y + dy[i], nx = x + dx[i];
			if (ny < 0 || ny >= n || grid[ny][nx] != '.' || vis[ny][nx]) continue;
			q.emplace(ny, nx, t + 1);
			vis[ny][nx] = true;
		}
	}

	assert(false);
}

int main () {
	string line;
	int start_x = -1;
	int end_x = -1;
	while (cin >> line) {
		m = (int)line.size();
		grid.push_back(line);
		for (int i = 0; i < m; i++) {
			if      (line[i] == '^') blizzards.emplace_back(n, i, 0);
			else if (line[i] == '>') blizzards.emplace_back(n, i, 1);
			else if (line[i] == 'v') blizzards.emplace_back(n, i, 2);
			else if (line[i] == '<') blizzards.emplace_back(n, i, 3);
		}
		n++;
	}

	for (int i = 0; i < m; i++) {
		if (grid[0][i] == '.') {
			assert(start_x == -1);
			start_x = i;
		}
		if (grid[n - 1][i] == '.') {
			assert(end_x == -1);
			end_x = i;
		}
	}
	assert(start_x != -1 && end_x != -1);

	int total_time = 0;
	total_time += bfs(0, start_x, n - 1, end_x) + 1;
	total_time += bfs(n - 1, end_x, 0, start_x) + 1;
	total_time += bfs(0, start_x, n - 1, end_x);

	cout << total_time << endl;
}
