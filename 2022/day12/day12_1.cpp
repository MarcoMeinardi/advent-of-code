#include <bits/stdc++.h>
using namespace std;

int n, m;
vector <string> grid;

const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

int bfs(pair <int, int> start, pair <int, int> finish) {
	vector <vector <bool>> vis(n, vector <bool> (m, false));

	queue <array <int, 3>> todo;

	todo.push({start.first, start.second, 0});

	while (!todo.empty()) {
		array <int, 3>& front = todo.front();
		int py = front[0], px = front[1], w = front[2];
		todo.pop();
		if (py == finish.first && px == finish.second) {
			return w;
		}
		if (vis[py][px]) continue;
		vis[py][px] = true;

		for (int i = 0; i < 4; i++) {
			int ny = py + dy[i], nx = px + dx[i];
			if (ny < 0 || ny >= n || nx < 0 || nx >= m ||
				vis[ny][nx] || grid[ny][nx] - grid[py][px] > 1) continue;

			todo.push({ny, nx, w + 1});
		}
	}
	assert(false);
}

int main () {
	string line;
	cin >> line;
	m = (int)line.size();
	do {
		grid.push_back(line);
	} while (cin >> line);

	n = (int)grid.size();

	pair <int, int> start, finish;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (grid[i][j] == 'S') {
				start = make_pair(i, j);
				grid[i][j] = 'a';
			} else if (grid[i][j] == 'E') {
				finish = make_pair(i, j);
				grid[i][j] = 'z';
			}	
		}
	}

	cout << bfs(start, finish) << endl;
}

